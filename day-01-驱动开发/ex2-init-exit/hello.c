#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE ("GPL");                  //版权声明


static int __init hello_2_init (void)     //自定义加载函数 
{
	printk (KERN_INFO "Hello world\n");
	return 0;
}

static void __exit hello_2_exit (void)     //自定义卸载函数
{
	printk (KERN_INFO "Goodbye world\n");
}


module_init (hello_2_init);//dmesg  ：显示内核缓冲区内容
module_exit (hello_2_exit);//dmesg  ：显示内核缓冲区内容

//将自定义的 加载\卸载函数名 向内核声明成 加载\卸载函数
                            