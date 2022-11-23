#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE2(2dmemcpy, float **, input, float **, output)
{
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            long copy = __copy_from_user(&output[i][j],&input[i][j],4);
            if(copy){
                return -EFAULT;
            }
        }
    }

    return 0;
}