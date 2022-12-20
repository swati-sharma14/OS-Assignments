#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.H>
#include <pthread.h>

int sticks[5];

void* philo(void* t){
    while(sticks[*((int *)t)]==0 &&(sticks[(*((int *)t)+1)%5]==0));
  
    sticks[*((int *)t)]=0;
    sticks[(*((int *)t)+1)%5]=0;

    printf("Philosopher %d is eating \n",*((int *)t));
    sleep(1);

    sticks[*((int *)t)]=1;
    sticks[(*((int *)t)+1)%5]=1;

}

int main(){
    int arr[5];
    pthread_t philoid[5];

    for(int i=0; i<5; i++){
        sticks[i] = 1;
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
