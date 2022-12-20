#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>


int main(){
    key_t key = ftok("./file", 'W');
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
    
    char* buf = ptr;

    int j = 0;
    char highest[3];
    for(int k=0; k<5; k++){
        if(k==4){
            highest[0] = buf[j];
            highest[1] = buf[j+1];
            highest[2] = '\0';
        }
        while(buf[j]<='9' && buf[j]>='0'){
            printf("%c",buf[j]);
            j++;
        }
        printf(" ");
        for(int a = 0; a<5; a++){
            printf("%c",buf[j]);
            j++;
        }

        printf("\n");  
    }

    memcpy(ptr, highest, strlen(highest));
    
    shmdt(ptr);
    printf("\n");
}
