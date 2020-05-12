#include <stdio.h>
#include <pthread.h>
void ∗ h ello (void * tid ) {
    printf("Hello from thread %d\n" , (int)tid ) ;
}
int main() {
    pthread_t tid [ 1 0 ] ;
    int i;
    for ( i = 0; i < 10; i++) {
        pthread_create(&tid [ i ] , NULL, hello , (void∗)i) ;
    }
    pthread_exit (NULL)
}