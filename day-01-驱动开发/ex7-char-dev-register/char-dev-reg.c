#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE ("GPL");

int hello_major = 256;
int hello_minor = 0;
int number_of_devices = 1;

struct cdev cdev;                      //定义 cdev结构体
dev_t dev = 0;



/*-----方法：hello_fops结构体   ||    cdev结构体        devno ----------*/
/*------------  定义并初始化 ------- 类字符设备结构体 | 属性设备号------*/
struct file_operations hello_fops = {   ////  <<======>>
  .owner = THIS_MODULE                  /***** (法一) *****/
};



static void char_reg_setup_cdev (void)  ////  ======>>
{
  int error, devno = MKDEV (hello_major, hello_minor);
  
  cdev_init (&cdev, &hello_fops);      //初始化  //操作方法：file_operations  hello_ops;
  cdev.owner = THIS_MODULE;
  
  error = cdev_add (&cdev, devno , 1); //注册 cdev结构体
  if (error)
    printk (KERN_NOTICE "Error %d adding char_reg_setup_cdev", error);

}

/*****************加载函数*******************/
static int __init hello_2_init (void)
{
  int result;
  dev = MKDEV (hello_major, hello_minor);
  result = register_chrdev_region (dev, number_of_devices, "hello");        //!  注册的可以不使用
  if (result<0) {
    printk (KERN_WARNING "hello: can't get major number %d\n", hello_major);
    return result;
  }
  char_reg_setup_cdev ();                ////  <<=======                     //!
  printk (KERN_INFO "Registered character driver\n");
  return 0;
}



/*****************卸载函数*******************/
static void __exit hello_2_exit (void)
{
  dev_t devno = MKDEV (hello_major, hello_minor);
  
  cdev_del (&cdev);                       //释放 cdev结构体

  unregister_chrdev_region (devno, number_of_devices);

  printk (KERN_INFO "Char driver cleaned up\n");
}



module_init (hello_2_init);
module_exit (hello_2_exit);