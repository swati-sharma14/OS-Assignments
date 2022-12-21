#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <time.h>


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
//        printf("%s\n",arr[i]);
    }

    char *name = "./socketsocketsocketsocket";

    int rock = socket(AF_UNIX, SOCK_STREAM, 0);
    if(rock==-1){
        perror("Socket error");
        exit(0);
    }

    struct sockaddr_un sock1;
    sock1.sun_family = AF_UNIX;
    strcpy(sock1.sun_path,name);
    unlink(sock1.sun_path);
    unsigned int len = strlen(sock1.sun_path)+1 + sizeof(sock1.sun_family);
    
    int a = bind(rock, (struct sockaddr *)&sock1, len);
    if(a==-1){
        perror("Bind error");
        exit(0);
    }
    if(listen(rock,1) == -1){
        perror("Listen error");
        exit(0);
    }


    len = sizeof(struct sockaddr_un);
    struct sockaddr_un sock2;

    int sent = 0;
    clock_t t = clock();
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
            int j;
            for(j=sent; j<sent+5;j++){
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
            sent+=4;
            str[strlen(str)] = '\0';
	    
	    int s2 = accept(rock,(struct sockaddr *)&sock2,(socklen_t *)&len);
            if(s2==-1){
                perror("accept");
                exit(0);
            }

            if(send(s2,str,strlen(str)+1,0) <0){
                perror("Send");
                exit(0);
            }

            wait(NULL);

           
            char buf[3];
            
            if(recv(s2,buf,3,0) < 0){
                perror("Receive");
                exit(0);
            }

            int bc;
            bc = (10*((int)(buf[0] - '0')));
            bc += (int)(buf[1] - '0');


            if(sent!=bc){
                printf("indices dont match\n");
            }
            sent = bc;
            sent++;
        }
    }

    close(rock);
    unlink(name);
    t = clock() - t;
    printf("Time taken by socket : %f ", t);
}
