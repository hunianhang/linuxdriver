#include "linux/fs.h"
#include "linux/types.h"
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/delay.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/capability.h>
#include <linux/init.h>
#include <linux/mutex.h>

static int major;
static unsigned char hello_buf[100];
//(struct inode *, struct file *);
static int char_open(struct inode *inode, struct file *filp){
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return 0;
}

static int char_release(struct inode *inode, struct file *filp){
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return 0;
}
static ssize_t char_read(struct file *filp, char __user *buf, size_t size, loff_t *offset){
    unsigned long length = size > 100? 100: size;
    copy_to_user(buf,hello_buf,length);
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return length;
}

static ssize_t char_write(struct file *filp, const char __user *buf, size_t size, loff_t *offset){
    unsigned long  length = size>100? 100:size;
    copy_from_user(hello_buf,buf, length);
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);

    return length;
}

static struct file_operations fops= {
    .owner = THIS_MODULE,
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .release = char_release,
    // .unlocked_ioctl = ;
};

static struct class *hello_class;
#define CLASS_NAME  "hello_class"

static int hello_init(void){

    major = register_chrdev(0, "CharDevice", &fops);

    hello_class = class_create(CLASS_NAME);
    if (IS_ERR(hello_class)) {
		pr_err("%s: couldn't create class\n", __FILE__);
		return PTR_ERR(hello_class);
	}

    device_create(hello_class,NULL,MKDEV(major,0),NULL,"hello");

    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return 0;
}

static void hello_exit(void){
    device_destroy(hello_class, MKDEV(major,0));
    class_destroy(hello_class);
    unregister_chrdev(major,"CharDevice");
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");