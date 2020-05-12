#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int Calculate(int N){
    int i =0;
    int count = 0;
    for (i =0; i < N; i++){
        float x = (float)rand()/(float)(RAND_MAX)*1.0;
        float y = (float)rand()/(float)(RAND_MAX)*1.0;
        if (x*x+y*y<=1) count +=1;
    }
    return count;
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
    int N = atoi(argv[1]);
    int In = Calculate(N);
    float pi = 4*(float)In/N;
    printf("%f\n",pi);
    clock_t end = clock();
    double time_spent = (double)(end - begin)/ CLOCKS_PER_SEC;
    printf("%lf",time_spent);
}