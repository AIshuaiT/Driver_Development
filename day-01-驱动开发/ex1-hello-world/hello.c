#include <linux/module.h>
#include <linux/kernel.h>

MODULE_LICENSE ("GPL");                //版权声明

int __init init_module (void)          //缺省加载函数
{
  printk (KERN_INFO "Hello world\n");
  return 0;
}

void __exit cleanup_module (void)      //缺省卸载函数
{
  printk (KERN_INFO "Goodbye world\n");
}
