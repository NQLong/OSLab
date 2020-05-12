#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long int In= 0;

void* Calculate(void* Num){
    int N =(int)Num;
    
    int i =0;
    int count = 0;
    for (int i =0; i < N; i++){
        float x = (float)rand()/(float)(RAND_MAX);
        float y = (float)rand()/(float)(RAND_MAX);
        if (x*x+y*y<=1) count +=1;
    }

    In+=count;

    pthread_exit(0);
}

int main(int argc,char ** argv){
    clock_t begin = clock();
    if(argc!=2){
        fprintf(stderr,"usage: a.out <integer value>\n");
        return-1;
    }
    if(atoi(argv[1])<0){
        fprintf(stderr,"%d must be>=0\n",atoi(argv[1]));
        return-1;
    }
    pthread_t tid[2];
    pthread_attr_t attr;
    long int N = atoi(argv[1]);
    /*get the default attributes*/
    pthread_attr_init(&attr);
    /*create the thread*/
    for (int i = 0;i < 4; i++)
        pthread_create(&tid[i],&attr,Calculate,(void*)(N/4));
    /*wait for the thread to exit*/
    for (int i = 0;i < 4; i++)
        pthread_join(tid[i],NULL);
    printf("%d\n",In);
    float pi = 4*(float)In/N;
    printf("%f\n",pi);
    clock_t end = clock();
    double time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("%lf",time_spent);
}