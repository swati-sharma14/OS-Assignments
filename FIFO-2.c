#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


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
    int fd = open("fifa", O_RDONLY);
    if(fd == -1){
        perror("File opening failed\n");
        exit(0);
    }
    
    char* str;
    char buf[50];

    int nm = read(fd, buf, 40);
    close(fd);
    if(nm == (-1)){
        perror("Write");
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

        int fd1 = open("fifa", O_WRONLY);
        int nmu = write(fd1, highest, strlen(highest));
        close(fd1);
    }
    // s
}
