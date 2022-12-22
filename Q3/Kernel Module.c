#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <linux/pid.h>


MODULE_LICENSE("OS");
MODULE_AUTHOR("2021568");
MODULE_DESCRIPTION("Kernel Module");

int pid;
module_param(pid, int,  S_IRUSR);

static int __init hello_init(void){
    struct pid* p;
    struct task_struct *s;
    
    p = find_get_pid(pid);
    s = get_pid_task(p,PIDTYPE_PID);
    
    if(p==NULL){
        exit(0);
    }

    printk(KERN_INFO "Process id : %d \n", pid);
    printk(KERN_INFO "The real user ID is %d\n", getuid());
    printk(KERN_INFO "The effective user ID is %d\n", geteuid());
    printk(KERN_INFO "The process group ID is %d\n", getpid(pid));
    printk(KERN_INFO "The command line path of the process is %s\n", pwdx(pid));
    return 0;
}

static void __exit hello_exit(void){
    printk(KERN_INFO"Bye :D \n");
}

module_init(hello_init);
module_exit(hello_exit);
