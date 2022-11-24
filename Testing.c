#include <stdio.h>
#include <sys/syscall.h>
#include <linux/kernel.h>
#include <unistd.h>
#include <errno.h>

#define TWODMEMCPY 451

void check_equal(float** lhs, float** rhs){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            if(lhs[i][j] != rhs[i][j]){
                printf("Error : LHS[%d] != RHS[%d]\n", i, i);
                return;
            }
        }
    }

    printf("Message : Success LHS = RHS \n");
}

int main(){
    float source[2][2] = {{1.0, 2.0}, {1.1, 2.1}};
    float destination[2][2]; 

    long status;

    status = syscall(TWODMEMCPY, source, destination);

    if (status != EFAULT){
        printf("Message : System Call 451 successfuly invoked \n");
        check_equal(source, destination);
    }
    return 0;
}
