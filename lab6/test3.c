#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define MAX_THREADS 4


long int total=0;
long int valid=0;
pthread_mutex_t lock;

/*
 * name:        Calculate
 * return type: void*
 * @param:      Num - a void pointer keep value of number of dots 
 * goal:        generate Num of random dots and calculate how
 *              many dots are there inside the circle with radius of 1
 *      
*/

float *Arr[2];
void * Calulate(void * param){
    long int i,begin = (long int)param,count = 0;
    for (i = 0; i< total/MAX_THREADS;i++)
        if (Arr[0][begin+i]*Arr[0][begin+i]+Arr[1][begin+i]*Arr[1][begin+i]<=1) count +=1;
    pthread_mutex_lock(&lock);
        valid+=count;
    pthread_mutex_unlock(&lock);
}

// struct Cparamater {
//     int begin;
//     int end;
// };

int main(int argc,char ** argv) {
    clock_t begin= clock();
    if(argc!=2){
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    if(atol(argv[1])<0){
        fprintf(stderr,"%d must be>=0\n",atoi(argv[1]));
        return -1;
    }

    total = atol(argv[1]);
    
    const long int N = total;
    const int test = 2;
    Arr[0] = (float*)(malloc(sizeof(float)*N));
    Arr[1] = (float*)(malloc(sizeof(float)*N));
    long int i = 0;
    for (i = 0; i < N;i++){
        Arr[0][i]=(float)rand()/(float)(RAND_MAX);
        Arr[1][i]=(float)rand()/(float)(RAND_MAX);
    }

    pthread_t pthID[MAX_THREADS];

    for (i = 0; i< MAX_THREADS;i++) {
        pthread_create(&pthID[i],NULL,Calulate,(void*)(total/MAX_THREADS*i));
    }

    for (i = 0; i< MAX_THREADS;i++) {
        pthread_join(pthID[i],NULL);
    }

    printf("%lf\n",(double)valid/total*4);
    clock_t end =clock();
    double time = (double)(end-begin)/CLOCKS_PER_SEC;
    printf("%lf\n",time);
}