#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>


char* generate(){
    char *send = (char *) malloc(6*sizeof(char));
    for(int i=0;i<5;i++){
        int a = (rand() % (26));
        send[i] = (char)((int) 'a'+a);
    }
    send[5] = '\0';
    return send;
}

int main(){
    char** arr = (char **) malloc(50*sizeof(char *));
    for(int i=0;i<50;i++){
        arr[i] = generate();
    }

    key_t key = ftok("./file", 'A');
    int shmid = shmget(key, 1024, 0644 | IPC_CREAT);
    if(shmid < 0){
        perror("shmid failed");
        exit(0);
    }
    char* ptr = (char*) shmat(shmid, NULL, 0);
    if(ptr == (char* ) -1){
        perror("shmat error");
        exit(0);
    }

    int sent = 0;
    for(int i=0;i<10;i++){
        pid_t pid = fork();
        if(pid<0){
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        else if(!pid){
            execl("./p2",NULL);
            exit(EXIT_SUCCESS);
        }
        else{
            char* str = malloc(50*sizeof(char));
            for(int j=sent; j<sent+5; j++){
                char ind[3];
                if(j<10){
                    ind[0] = '0';
                    ind[1] = (char) ('0' + j);
                }
                else{
                    ind[0] = (char) ('0' + j/10);
                    ind[1] = (char) ('0' + j%10);
                }
                ind[2] = '\0';
                strcat(str,ind);
                strcat(str,arr[j]);
            }
	    sent += 4;
            
            memcpy(ptr, str, strlen(str));

            wait(NULL);

            char* ptrptr = ptr;
            char received[2];
            received[0] = *ptrptr;
            ptrptr++;
            received[1] = *ptrptr;
            int bc;
            bc = (10*((int)(received[0] - '0')));
            bc += (int)(received[1] - '0');
	    //printf("%i %i\n",sent,bc);
            if(sent != bc){
                perror("indices dont match");
            }
            sent = bc;
	    sent++;
        }
    }
    shmdt(ptr);
    shmctl(shmid,IPC_RMID,NULL);
}
