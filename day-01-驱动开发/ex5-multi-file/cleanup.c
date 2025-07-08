#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>


static void __exit hello_2_exit (void)
{
	printk (KERN_INFO "Goodbye world\n");
}


module_exit (hello_2_exit);