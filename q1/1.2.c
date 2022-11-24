#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <time.h>
#include <sys/wait.h>
#include <stdlib.h>

struct sched_param p1,p2,p3;

pid_t pid1, pid2, pid3 ;

struct timespec start1 , stop1 , start2 , stop2 , start3 , stop3;

char *a1 = "/bin/bash";
char *a2 = "/bin/bash";

int main(){
    clock_gettime( CLOCK_REALTIME, &start1);
    p1.sched_priority = 0;
    sched_setscheduler(pid1,SCHED_OTHER,&p1);
    nice(15);
    pid1 = fork();

    if(pid1 < 0){
        perror("Fork failed to generate a child process");
    }

    if(pid1==0){
        execl(a1,a2,"bash1.sh",(char *) NULL);
        exit(0);
    }

    else{

        clock_gettime( CLOCK_REALTIME, &start2);
        p2.sched_priority = 1;
        sched_setscheduler(pid2,SCHED_FIFO,&p2);

        pid2 = fork();

        if(pid2 < 0){
            perror("Fork failed to generate a child process");
        }

        if(pid2==0){
            execl(a1,a2,"bash2.sh",(char *) NULL);
            exit(0);
        }

        else{
            clock_gettime( CLOCK_REALTIME, &start3);
            p3.sched_priority = 1;
            sched_setscheduler(pid3,SCHED_RR,&p3);

            pid3 = fork();

            if(pid3 < 0){
                perror("Fork failed to generate a child process");
            }

            if(pid3==0){
                execl(a1,a2,"bash3.sh",(char *) NULL);
                exit(0);
            }

            else{
                wait(NULL);
                clock_gettime(CLOCK_REALTIME,&stop3);
            }

            wait(NULL);
            clock_gettime(CLOCK_REALTIME, &stop2);
        }
        wait(NULL);
        clock_gettime(CLOCK_REALTIME,&stop1);
    }
    if(stop1.tv_nsec - start1.tv_nsec < 0L){
        stop1.tv_sec -= 1;
        stop1.tv_nsec += 1000000000L;
    }
    if(stop2.tv_nsec - start2.tv_nsec < 0L){
        stop2.tv_sec -= 1;
        stop2.tv_nsec += 1000000000L;
    }
    if(stop3.tv_nsec - start3.tv_nsec < 0L){
        stop3.tv_sec -= 1;
        stop3.tv_nsec += 1000000000L;
    }

    printf("%i.%li seconds\n", stop1.tv_sec - start1.tv_sec, stop1.tv_nsec - start1.tv_nsec);
    printf("%i.%li seconds\n", stop2.tv_sec - start2.tv_sec, stop2.tv_nsec - start2.tv_nsec);
    printf("%i.%li seconds\n", stop3.tv_sec - start3.tv_sec, stop3.tv_nsec - start3.tv_nsec);

}
