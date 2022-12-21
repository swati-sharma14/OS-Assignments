#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>
#include <unistd.h>


MODULE_LICENSE("OS");
MODULE_AUTHOR("2021568");
MODULE_DESCRIPTION("Kernel Module");

module_param(pid, int,  S_IRUSR | S_IWUSR);
int pid = getpid();

static int start(void){
    struct task_struct *p = NULL;
    p = find_task_by_vpid(pid);
    if(p==NULL){
        perror("Task not found");
        exit(0);
    }

    printk(KERN_INFO "Process id : %d \n", pid);
    printk(KERN_INFO "The real user ID is %d\n", getuid());
    printk(KERN_INFO "The effective user ID is %d\n", geteuid());
    printk(KERN_INFO "The process group ID is %d\n", getpid(pid));
    printk(KERN_INFO "The command line path of the process is %s\n", pwdx(pid));

}

static void exit(void){
    pr_debug("Bye :D \n");
}

module_init(start);
module_exit(exit);