//static /* const */ DEVICE_ATTR(pincount, 0644,
//                app_comm_pincount_show, app_comm_pincount_store);

/*static struct class gpio_class = {
        .name =         "app_comm",
        .owner =        THIS_MODULE,

        .class_attrs =  gpio_class_attrs,
};*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/sysdev.h>
#include <linux/major.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/cdev.h>
#include <linux/kdev_t.h>


//#define MAJOR_NUM 200
//#define DEVICE_NAME "cdev"

int pincount = 10;

static DEFINE_MUTEX(sysfs_lock);

static ssize_t app_comm_pincount_show(struct device *dev,
                struct device_attribute *attr, char *buf);
//static ssize_t app_comm_pincount_store(struct device *dev,
//                struct device_attribute *attr, const char *buf, size_t size);

//static struct file_operations fops;

static struct class_attribute app_comm_class_attr[] = {
	//__ATTR(pincount, 0644, app_comm_pincount_show, app_comm_pincount_store),
	__ATTR(pincount, 0644, app_comm_pincount_show, NULL),
	__ATTR_NULL
};

static struct class app_comm_drv = {
	.name = "app_comm",
	.owner = THIS_MODULE,
	.class_attrs = &app_comm_class_attr,
};

static ssize_t app_comm_pincount_show(struct device *dev,
                struct device_attribute *attr, char *buf)
{
	ssize_t status;

	mutex_lock(&sysfs_lock);
	
	status = sprintf(buf, "%d\n", pincount);
	
	mutex_unlock(&sysfs_lock);
	return status;
}

/*static ssize_t app_comm_pincount_store(struct device *dev,
                struct device_attribute *attr, const char *buf, size_t size) {
{
	return size;
}*/


static int app_comm_init(void)
{
	int status;
	/*status = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
	if(status < 0)
	printk("Registering char driver failed with status = %d\n", status);
	else*/
	printk("Hello World\n");

	status = class_register(&app_comm_drv);
	if(status < 0)
		printk("Registering Class Failed\n");

	return 0;
}

static void app_comm_exit(void)
{
	class_unregister(&app_comm_drv);
	//unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
	printk(" GoodBye, world\n");
}

module_init(app_comm_init);
module_exit(app_comm_exit);
MODULE_LICENSE("GPL");