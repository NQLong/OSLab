#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_THREADS 4
long ValidPoint = 0;
long ThreadPoints;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


/* @name    : Calculate_0
 * @param   : Param, type: void* , just in case inneed
 * @goal    : generate n point with coordinate (x,y) where
 *            0<x,y<1 and then calculate if they are in the 
 *            first quater of a circle with radius 1 and its
 *            centre is the origin.
 * @approach: use random fuction provide by stblib.h library to generate point
 *            then calculate its distance from origin. if the distance smaller
 *            than 1, its a valid point(inside the quarter circle).
 * @Note    : in this funtion we use a local varible to hole the number of valid
 *            point before we update it to the globle variable ValidPoint, which
 *            hold the number of valid point of all thread.
 */
void *Calculate_0(void* Param){
    long count = 0;

    unsigned int ThreadState = rand();
    long i;
    for (i = 0; i < ThreadPoints; i++) {
        /* Becasue the rand() use a shared state in threads so when
         * when we use it in muti-threads program it would be thread
         * unsafe.
         * the idea to solve this problem is we use rand() to gennerate
         * a state that will be used as seed for rand_r(seed) in each thread
        */
        double x = (double)rand_r(&ThreadState) / RAND_MAX;
        double y = (double)rand_r(&ThreadState) / RAND_MAX;

        if (x * x + y * y < 1) {
            count += 1;
        }
    }
    /* lock mutex because the ValidPoint is global and shared among threads*/
    pthread_mutex_lock(&mutex);
    ValidPoint +=count;
    pthread_mutex_unlock(&mutex);
    return NULL;
}
/* @name    : Calculate_1
 * @param   : Param, type: void* , just in case inneed
 * @goal    : sam as func Calculate_0
 * @approach: sam as func Calculate_0
 * @Note    : in this funtion we update the global var ValidPoint
 *            everytime we have a validpoint
 */
void *Calculate_1(void* Param) {
    unsigned int ThreadState = rand();
    
    /* in this function, we will lock mutex from begin of the funtion
     * and update to global variable, which store the number of points that is
     * inside of circle radius 1, everytime we have a valid point*/
    
    pthread_mutex_lock(&mutex);
    long i;
    for (i = 0; i < ThreadPoints; i++) {
        double x = (double)rand_r(&ThreadState) / RAND_MAX;
        double y = (double)rand_r(&ThreadState) / RAND_MAX;
        if (x * x + y * y < 1) {
            ValidPoint += 1;
        }
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

/* this program is made for calculate pi 
 * we 2 approuches which are multithread and single thread
 * we will compare the multithread approuch and single thread
 * in multithread we also compare which is the best way to use mutex_lock.
 * @Note: use 1000000000 for easy to compare the time execute */
int main(int argc, const char *argv[])
{
    if(argc!=2){
        fprintf(stderr,"usage: a.out <integer value>\n");
        return -1;
    }
    if(atoi(argv[1])<0){
        fprintf(stderr,"%d must be>=0\n",atoi(argv[1]));
        return -1;
    }

    long totalpoints = atol(argv[1]);
    ThreadPoints = totalpoints / MAX_THREADS;


    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    /* start calculate pi with multithread, use Calculate_0 to count pi.*/
    time_t start_0 = time(NULL);    //set a timer for easy to compre efficiency
    pthread_t tid[MAX_THREADS];

    pthread_attr_t attr;        
    pthread_attr_init(&attr);
    printf("pi_cal multithread verse_0 :\n");
    /*create threads to calculate parallel, in this case 4 threads*/
    int i;
    for (i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tid[i], &attr, Calculate_0, (void *) NULL);
    }
    /*wait for all threads finishing its job*/
    for (i = 0; i < MAX_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    /*print out the result and its execute time*/
    
    printf("Pi: %f\n", (4. * (double)ValidPoint) / (ThreadPoints * MAX_THREADS));
    printf("Time: %ld sec\n\n", (time(NULL) - start_0));
    /*finish first approuch*/
    ////////////////////////////////////////////////////////////////////////////////////////////////////



    /////////////////////////////////////////////////////////////////////////////////////////////////
    /* start calculate pi with multithread, use Calculate_1 to count pi.*/
    time_t start_1 = time(NULL);    //set a timer for easy to compre efficiency
    printf("pi_cal multithread verse_1 :\n");
    /*create threads to calculate parallel, in this case 4 threads*/
    //reuse the thread id and some local variable
    ValidPoint = 0;  //reset valid point
    for (i = 0; i < MAX_THREADS; i++) {
        pthread_create(&tid[i], &attr, Calculate_1, (void *) NULL);
    }
    /*wait for all threads finishing its job*/
    for (i = 0; i < MAX_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    /*print out the result and its execute time*/
    
    printf("Pi: %f\n", (4. * (double)ValidPoint) / (ThreadPoints * MAX_THREADS));
    printf("Time: %ld sec\n\n", (time(NULL) - start_1));
    /*finish first approuch*/
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////////////////////////////////////
    /* calculate pi with single thread*/
    ThreadPoints = totalpoints;
    ValidPoint = 0;
    printf("pi_cal serial:\n");
    time_t start_2 = time(NULL);
    Calculate_0(NULL);  /*we can reuse calculate_0 or calculate_1 because 
                it would be the same when using singgle thread*/
    
    printf("Pi: %f\n", (4. * (double)ValidPoint) / ThreadPoints);
    printf("Time: %ld sec\n", (time(NULL) - start_1));
    //////////////////////////////////////////////////////////////////////////////////////////////
    return 0;
}