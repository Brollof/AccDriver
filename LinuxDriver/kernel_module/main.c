#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#include "accel.h"

#define DEV_NAME "accel"
#define LOG_PREFIX "["DEV_NAME" dev] "

static int dev_open(struct inode *inode, struct file *fp);
static ssize_t dev_read(struct file *fp, char __user *buf, size_t, loff_t *offset);
static ssize_t dev_write(struct file *fp, const char __user *buf, size_t, loff_t *offset);
static int dev_release(struct inode *inode, struct file *fp);

static int major_num = 0;
static struct file_operations fops =
{
  .open = dev_open,
  .read = dev_read,
  .write = dev_write,
  .release = dev_release
};

static int dev_open(struct inode *inode, struct file *fp)
{
  printk(KERN_INFO LOG_PREFIX "Open\n");
  accInit();
  return 0;
}

static ssize_t dev_read(struct file *fp, char __user *buf, size_t len, loff_t *offset)
{
  printk(KERN_INFO LOG_PREFIX "Read\n");
  return 0;
}

static ssize_t dev_write(struct file *fp, const char __user *buf, size_t len, loff_t *offset)
{
  printk(KERN_INFO LOG_PREFIX "This device is not writable!\n");
  return -EFAULT;
}

static int dev_release(struct inode *inode, struct file *fp)
{
  printk(KERN_INFO LOG_PREFIX "Release\n");
  accDeinit();
  return 0;
}

static int __init moduleInit(void)
{
  major_num = register_chrdev(0, DEV_NAME, &fops);
  if (major_num < 0)
  {
    printk(KERN_WARNING LOG_PREFIX "Registering char dev failed! err: %d\n", major_num);
    return major_num;
  }
  printk(KERN_INFO LOG_PREFIX "Registered with major number: %d\n", major_num);
  return 0;
}

static void __exit moduleExit(void)
{
  unregister_chrdev(major_num, DEV_NAME);
  printk(KERN_INFO LOG_PREFIX "device exit\n");
}

module_init(moduleInit);
module_exit(moduleExit);
