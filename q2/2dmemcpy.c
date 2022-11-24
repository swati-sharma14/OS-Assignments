#include <linux/kernel.h>
#include <linux/syscalls.h>


SYSCALL_DEFINE2(2dmemcpy, float **, input, float **, output)
{
    float buffer[2][2];
    
    long copy = __copy_from_user(buffer, input, sizeof(float)*4);
    if(copy) return -EFAULT;
    copy = __copy_to_user(output, buffer, sizeof(float)*4);
    if(copy) return -EFAULT;

    return 0;
}
