#include <stdio.h>
#include <stdlib.h>
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
        // printf("%s\n",arr[i]);
    }

    int a = mknod("fifa", S_IFIFO | 0666, 0); 
    if(a == -1){
        perror("mknod failed \n");
        exit(0);
    }

    int sent = 0;
    for(int i=0;i<10;i++){
        int fd = open("fifa", O_WRONLY);
        if(fd == -1){
            perror("File opening failed\n");
            exit(0);
        }
        char* str;
        for(int j=sent; j<sent+5;j++){
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
        
        int nm = write(fd, str, strlen(str));
        close(fd);

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
            
            fd = open("fifa", O_RDONLY);
            if(fd == -1){
                perror("File opening failed\n");
                exit(0);
            }

            if(nm ==  (-1)){
                perror("Write");
            }
            char received[3];
            int num = read(fd, received, 2);
            if(num == (-1)){
                perror("Read");
            }
            int bc;
            bc = (10*((int)(received[0] - '0')));
            bc += (int)(received[1] - '0');

            if(sent != bc){
                perror("Bleh");
            }
            sent = bc;
            close(fd);
            sent++;
        }
    }
    // a

    unlink("fifa");
}
