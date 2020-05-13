#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define MAX_THREADS 5
clock_t begin;
clock_t serialTime;

long int In= 0;
pthread_mutex_t lock;

void* Calculate(void* Num){
    int N =(int)Num;
    int i =0;
    int count = 0;
    for (i =0; i < N; i++){
        float x = (float)rand()/(float)(RAND_MAX);
        float y = (float)rand()/(float)(RAND_MAX);
        if (x*x+y*y<=1) count +=1;
    }
    
    pthread_mutex_lock(&lock); 
    In+=count;
    pthread_mutex_unlock(&lock);

    pthread_exit(0);
}

void* Serial(void* Num){
    clock_t serialBegin = clock();
    int N = (int)Num;
    int count = 0;
    int i =00;
    for (i =0; i < N; i++){
        float x = (float)rand()/(float)(RAND_MAX);
        float y = (float)rand()/(float)(RAND_MAX);
        if (x*x+y*y<=1) count +=1;
    }
    clock_t serialEnd = clock();
    serialTime = serialEnd - serialBegin;
}

int main(int argc,char *argv[]){
    begin = clock();
    if(argc!=2){
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    if(atoi(argv[1])<0){
        fprintf(stderr,"%d must be>=0\n",atoi(argv[1]));
        return -1;
    }
   
    pthread_t tid[MAX_THREADS];
    pthread_attr_t attr;
    long int N = atoi(argv[1]);
   

    pthread_attr_init(&attr);

    int i = 0;
    for (i = 0;i < MAX_THREADS; i++){
        if (i != MAX_THREADS-1)
            pthread_create(&tid[i],&attr,Calculate,(void*)(N/4));
        else 
            pthread_create(&tid[i],&attr,Serial,(void*)(N));
    }
    clock_t Xtime;
    for (i = 0;i < MAX_THREADS; i++) {
        pthread_join(tid[i],NULL);
        if (i==MAX_THREADS - 2) 
            Xtime = clock() - begin;
    }
    
    double Mul_time_spent = (double)Xtime/ CLOCKS_PER_SEC;
    double Se_time_spent = (double)serialTime/ CLOCKS_PER_SEC;
    double pi = 4*(float)In/N;
    printf("pi = %lf\n",pi);
    printf("multi-thread 's execute time %lf\n", Mul_time_spent);
    printf("single-thread 's execute time %lf\n", Se_time_spent);
    double speed_up;
    if (!(Se_time_spent == 0.0 || Mul_time_spent == 0.0)){
        speed_up = Se_time_spent/Mul_time_spent;
        printf("speed-up : %lf",speed_up);
    } else {
        printf("cant calculate speed-up");
    }
}