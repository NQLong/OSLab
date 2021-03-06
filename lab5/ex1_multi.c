#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

clock_t begin;

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
    clock_t end = clock();
    double time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("%lf finish time\n",time_spent);fflush(stdout);
    pthread_mutex_lock(&lock); 
    In+=count;
    pthread_mutex_unlock(&lock); 
    pthread_exit(0);
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
   
    pthread_t tid[4];
    pthread_attr_t attr;
    long int N = atoi(argv[1]);
   
    /*get the default attributes*/
    pthread_attr_init(&attr);
    /*create the thread*/
    int i = 0;
    for (i = 0;i < 4; i++)
        pthread_create(&tid[i],&attr,Calculate,(void*)(N/4));
    /*wait for the thread to exit*/
    for (i = 0;i < 4; i++)
        pthread_join(tid[i],NULL);
    printf("%ld counted\n",In);
    double pi = 4*(float)In/N;
    printf("%lf result\n",pi);
    clock_t end = clock();
    double time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("%lf time",time_spent);
}