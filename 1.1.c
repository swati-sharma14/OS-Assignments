#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>


struct sched_param p1,p2,p3;
pthread_t t1,t2,t3;

p1 = {.sched_priority = 1};
p2 = {.sched_priority = 1};
p3 = {.sched_priority = 1};

void* countA(){
    pthread schedsetparam(pthread_self(), SCHED_OTHER, &p1);
    nice(15);
    for(long long int i=0;i<(4294967296L);i++){

    }
}

void* countB(){
    pthread schedsetparam(pthread_self(), SCHED_RR, &p2);
    for(long long int i=0;i<(4294967296L);i++){
        
    }
}

void* countC(){
    pthread schedsetparam(pthread_self(), SCHED_FIFO, &p3);
    for(long long int i=0;i<(4294967296L);i++){
        
    }
}

int main(){
    timespec start1, stop1, start2, stop2, start3, stop3, 

    clock_gettime( CLOCK_REALTIME, &start1);
    pthread_create(&t1, NULL, &countA, NULL);
    
    clock_gettime( CLOCK_REALTIME, &start2);
    pthread_create(&t2, NULL, &countB, NULL);

    clock_gettime( CLOCK_REALTIME, &start3);
    pthread_create(&t3, NULL, &countC, NULL);

    pthread_join(t1, NULL);
    clock_gettime( CLOCK_REALTIME, &stop1);

    pthread_join(t2, NULL);
    clock_gettime( CLOCK_REALTIME, &stop1);

    clock_gettime( CLOCK_REALTIME, &stop3);
    pthread_join(t3, NULL);


}