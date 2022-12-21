#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>



int main(){
    int rock = socket(AF_UNIX, SOCK_STREAM, 0),s2;
    if(rock==-1){
        perror("Socket error");
        exit(0);
    }

    char *name = "./socketsocketsocketsocket";

    struct sockaddr_un sock1;
    sock1.sun_family = AF_UNIX;
    strcpy(sock1.sun_path,name);

    int len = strlen(sock1.sun_path) + 1 + sizeof(sock1.sun_family);

    if(connect(rock,(struct sockaddr *)&sock1,len) == -1){
        perror("Connect");
        exit(0);
    }
    
    char* str;
    char buf[50];
    
    if(recv(rock,buf,40,0) <0){
        perror("Receive");
        exit(0);
    }

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

    if(send(rock, highest, 3, 0) < 0){
        perror("Send");
        exit(0);
    }

    close(rock);
    
    printf("\n");

}
