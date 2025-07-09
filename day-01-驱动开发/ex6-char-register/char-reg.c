#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>

MODULE_LICENSE ("GPL");

int hello_major = 250;                 	//设备号 dev_t  dvno;
int hello_minor = 0;
int number_of_devices = 1;



/*****************加载函数*******************/
static int __init hello_2_init (void)
{
  int result;
  dev_t dev = 0;

  dev = MKDEV (hello_major, hello_minor);//创建设备号

  result = register_chrdev_region (dev, number_of_devices, "hello_device"); //静态注册
  if (result<0) {
    printk (KERN_WARNING "hello: can't get major number %d\n", hello_major);
    return result;
  }

  printk (KERN_INFO "Registered character driver\n");
  return 0;
}

/*****************卸载函数*******************/
static void __exit hello_2_exit (void)
{
  dev_t devno = MKDEV (hello_major, hello_minor);

  unregister_chrdev_region (devno, number_of_devices);                      //释放设备号

  printk (KERN_INFO "Char driver cleaned up\n");
}


module_init (hello_2_init);
module_exit (hello_2_exit);
