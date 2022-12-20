#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.H>
#include <semaphore.h>
#include <pthread.h>


sem_t sticks[5];

void* philo(void* t){
    sem_wait(&sticks[*((int *)t)]);
    sem_wait(&sticks[(*((int *)t)+1)%5]);

    printf("Philosopher %d is eating \n",*((int *)t));
    sleep(1);

    sem_post(&sticks[(*((int *)t)+1)%5]);
    sem_post(&sticks[*((int *)t)]);
}

int main(){
    int arr[5];
    pthread_t philoid[5];
    

    for(int i=0;i<5;i++){
        sem_init(&sticks[i], 0, 1);
        arr[i] = i;
    }

    for(int j=0; j<3678; j++){
        for(int i=0; i<5; i++){
            pthread_create(&philoid[i], NULL, philo, (void* )&arr[i]);
        }
        for(int i=0; i<5; i++){
            pthread_join(id[i], NULL);
        }
    }

}
