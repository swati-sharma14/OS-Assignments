#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWODMEMCPY 451


int main(){
    float source[2][2] = {{1.0, 2.0}, {1.1, 2.1}};
    float destination[2][2]; 

    long status;

    status = syscall(TWODMEMCPY, source, destination);

    if (status != EFAULT){
        printf("Message : System Call 451 successfuly invoked \n");
	int b = 0;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			if(source[i][j] != destination[i][j]){
				printf("%d %d",source[i][j],destination[i][j]);
				b = 0;
				break;
			}
		}
		if(b==1) break;
	}

	if(b==0) printf("yes\n");
	else printf("no\n");
    }
    return 0;
}
