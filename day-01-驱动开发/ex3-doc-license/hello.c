#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>

#define DRIVER_AUTHOR "farsight"
#define DRIVER_DESC   "A sample driver"
/****可以通过 modinfo xxx.ko 查看模块信息****/
MODULE_LICENSE ("GPL");                  //版权声明
MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_DESCRIPTION (DRIVER_DESC);
MODULE_SUPPORTED_DEVICE ("TestDevice");


static int __init hello_2_init (void)    //自定义加载函数
{
	printk (KERN_INFO "Hello world\n");
	return 0;
}

static void __exit hello_2_exit (void)   //自定义卸载函数
{
	printk (KERN_INFO "Goodbye world\n");
}


module_init (hello_2_init);//dmesg  ：显示内核缓冲区内容
module_exit (hello_2_exit);//dmesg  ：显示内核缓冲区内容
                           //可以看到module_exit对于函数中的打印语句
						   //可以看到module_init对于函数中的打印语句