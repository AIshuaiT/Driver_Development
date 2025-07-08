#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/stat.h>

#define DRIVER_AUTHOR "farsight"
#define DRIVER_DESC   "A sample driver"
/****可以通过 modinfo xxx.ko 查看模块信息****/
MODULE_LICENSE ("GPL");
MODULE_AUTHOR (DRIVER_AUTHOR);
MODULE_DESCRIPTION (DRIVER_DESC);
MODULE_SUPPORTED_DEVICE ("TestDevice");


static short int myshort = 1;                    	//1-- 在模块源码内部定义一个变量，并初始化。
static int myint = 420;
static long int mylong = 9999;
static char *mystring = "blah";
static int array[2]= {-1, -1};
static int arr_argc = 0;   						/*根据传参改变*/
                                          
module_param (myshort, short, 0400);             	//2-- 用module_param宏来声明 该变量 可以接收传参。
MODULE_PARM_DESC (myshort, "A short integer");   	//4-- 可选，添加参数信息 用 modinfo xxx.ko 查看
                                         
module_param (myint, int, 0600);                 	//module_param(参数名,参数类型,参数读/写权限)；
MODULE_PARM_DESC (myint, "An integer");

module_param (mylong, long, 0000);       
MODULE_PARM_DESC (mylong, "A long integer");

module_param (mystring, charp, 0000);
MODULE_PARM_DESC (mystring, "A character string");

module_param_array (array, int, &arr_argc, 0000);/*根据传参改变*/
//module_param_array (array, int, arr_argc, 0000); 	//for kernel<2.6.10
MODULE_PARM_DESC (array, "An array of integers");



/*****************加载函数*******************/
static int __init hello_2_init (void)               //3-- 在加载模块时，传输参数
{                                                   //sudo insmod  xxx.ko  p=200
	int i;
                                                           //传参
	printk (KERN_INFO "myshort is a short integer: %hd\n", myshort);
	printk (KERN_INFO "myint is an integer       : %d\n", myint);
	printk (KERN_INFO "mylong is a long integer  : %ld\n", mylong);
	printk (KERN_INFO "mystring is a string      : %s\n\n", mystring);	//用dmesg  ：显示内核缓冲区内容

	for (i=0; i<arr_argc; i++)					/*根据传参改变*/
		printk (KERN_INFO "array[%d] =           :%d\n",i, array[i]);
	printk (KERN_INFO "Got %d arguments in array\n", arr_argc);

	return 0;
}


/*****************卸载函数*******************/
static void __exit hello_2_exit (void)
{
	printk (KERN_INFO "hello driver cleaned up\n");
}


module_init (hello_2_init);
module_exit (hello_2_exit);
