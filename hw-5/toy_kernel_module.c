#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/time.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Riley Wen");
MODULE_DESCRIPTION("A Toy Kernel Module..");

static struct task_struct *thread;

int thread_func(void * arg)
{
    unsigned long j0, j1;
    int delay = 1*HZ;
    while (!kthread_should_stop())
    {
        j0 = jiffies;
        j1 = j0 + delay;
        printk(KERN_INFO "Riley_thread get scheduled");
        while (time_before(jiffies, j1))
            schedule();
    }
    return 0;

}

int mod_init (void) {
    char thread_name[]="Riley_thread";
    printk(KERN_INFO "Riley_thread under init.");
    thread = kthread_create(thread_func, NULL, thread_name);
    if (thread)
    {
        printk(KERN_INFO "Riley_thread was created successfully. Waking it up...");
        wake_up_process(thread);
    }
    return 0;
}

void mod_exit(void)
{
    int ret;
    ret = kthread_stop(thread);
    if(!ret)
        printk(KERN_INFO "Riley_thread stopped normally.\n");
    else
        printk(KERN_INFO "Riley_thread returned %d\n", ret);
}

module_init(mod_init);
module_exit(mod_exit);
