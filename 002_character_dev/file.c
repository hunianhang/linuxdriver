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

#define DEVICE_NAME "CharDevice"
static int major;

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
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return size;
}

static ssize_t char_write(struct file *filp, const char __user *buf, size_t size, loff_t *offset){
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return size;
}

static struct file_operations fops= {
    .owner = THIS_MODULE,
    .read = char_read,
    .write = char_write,
    .open = char_open,
    .release = char_release,
};

static int hello_init(void){
    major = register_chrdev(0, DEVICE_NAME, &fops);
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
    return 0;
}

static void hello_exit(void){
    unregister_chrdev(major, DEVICE_NAME);
    printk("file:%s,function:%s\n",__FILE__,__FUNCTION__);
}
module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");
