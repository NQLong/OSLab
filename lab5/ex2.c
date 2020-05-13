#include <stdio.h>
#include <pthread.h>
pthread_mutex_t lock;

void *hello (void *tid ) {

    printf("Hello from thread %d\n" , (int)tid ) ;

}
int main() {
    pthread_t tid [10] ;
    int i;
    for ( i = 0; i < 10; i++) {
        if (i>0) pthread_join(tid[i-1],NULL);
        pthread_create(&tid[i] , NULL, hello , (void*)i) ;
    }
    pthread_exit (NULL);
}