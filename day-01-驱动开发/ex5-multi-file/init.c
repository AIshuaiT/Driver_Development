#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE ("GPL");


static int __init hello_2_init (void)
{
	printk (KERN_INFO "Hello world\n");
	return 0;
}


module_init (hello_2_init);