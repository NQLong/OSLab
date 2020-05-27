#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define MAX_THREADS 5
clock_t begin;
clock_t serialTime;

long int In= 0;
pthread_mutex_t lock;

/*
 * name:        Calculate
 * return type: void*
 * @param:      Num - a void pointer keep value of number of dots 
 * goal:        generate Num of random dots and calculate how
 *              many dots are there inside the circle with radius of 1
 *      
*/
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

/*
 * name:        Serial
 * return type: void *
 * @param:      Num - a void pointer keep value of number of dots 
 * goal:        this is simulate to Calculate function but we just use
 *              this funtion for calculate the execute time of this
 *              program when we run on single thread
*/
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
    if(argc!=2){
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    if(atoi(argv[1])<0){
        fprintf(stderr,"%d must be>=0\n",atoi(argv[1]));
        return -1;
    }
   
    pthread_t tid[MAX_THREADS];
    pthread_attr_t attr[MAX_THREADS];
    long int N = atoi(argv[1]);
   

    

    int i = 0;
    begin = clock();
    //generate threads
    for (i = 0;i < MAX_THREADS; i++){
        pthread_attr_init(&attr[i]);
        if (i != MAX_THREADS-1)
            pthread_create(&tid[i],&attr[i],Calculate,(void*)(N/4));
        else 
            pthread_create(&tid[i],&attr[i],Serial,(void*)(N));
    }
    clock_t Xtime;
    //wait for all thread exit
    for (i = 0;i < MAX_THREADS; i++) {
        pthread_join(tid[i],NULL);
        if (i==MAX_THREADS - 2) 
            Xtime = clock() - begin;
    }
    //calculate execute time
    double Mul_time_spent = (double)Xtime/ CLOCKS_PER_SEC;          //this is Multi-thread execution time
    double Se_time_spent = (double)serialTime/ CLOCKS_PER_SEC;      //this is single-thread execution time
    double pi = 4*(float)In/N;                                      //calculate pi
    printf("pi = %lf\n",pi);
    printf("multi-thread 's execute time %lf\n", Mul_time_spent);
    printf("single-thread 's execute time %lf\n", Se_time_spent);

    //calculate speed-up
    double speed_up;                  
    if (!(Se_time_spent == 0.0 || Mul_time_spent == 0.0)){
        speed_up = Se_time_spent/Mul_time_spent;
        printf("speed-up : %lf",speed_up);
    } else {
        printf("cant calculate speed-up");
    }
    return 0;
}