#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int sticks[5];
int bowl[2];

void* philo(void* t){
    while((sticks[*((int *)t)]==0) && (sticks[(*((int *)t)+1)%5]==0) && (bowl[0]==1 || bowl[1]==1));
  
    int a;
    sticks[*((int *)t)]=0;
    sticks[(*((int *)t)+1)%5]=0;
    if(bowl[0]==1 && bowl[1]==1){
        bowl[0] = 0;
        a=0;
    }
    else if(bowl[0]==1 && bowl[1]==0){
        bowl[0] = 0;
        a=0;
    }
    else{
        bowl[1] = 0;
        a=1;
    }

    printf("Philosopher %d is eating\n",*((int *)t));
    sleep(1);

    bowl[a]=1;
    sticks[*((int *)t)]=1;
    sticks[(*((int *)t)+1)%5]=1;
    return NULL;
}

int main(){
    int arr[5];
    pthread_t philoid[5];

    for(int i=0; i<5; i++){
        sticks[i] = 1;
        arr[i] = i;
    }
    bowl[0] = 1;
    bowl[1] = 1;

    for(int j=0; j<3678; j++){
        for(int i=0; i<5; i++){
            pthread_create(&philoid[i], NULL, philo, (void* )&arr[i]);
        }
        for(int i=0; i<5; i++){
            pthread_join(philoid[i], NULL);
        }
    }
}
