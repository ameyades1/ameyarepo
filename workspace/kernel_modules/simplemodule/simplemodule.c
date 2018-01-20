#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>

MODULE_AUTHOR ("Ameya Deswandikar");
MODULE_DESCRIPTION ("A simple module");

static int number = 24601;
static char *word = "blueberry";

module_param (number, int, S_IRUGO);
module_param (word, charp, S_IRUGO);

int init_simple(void)
{
  printk ("in init module simple\n");
	printk ("number = %d, word = %s", number, word);
	return 0;
}


void cleanup_simple(void)
{
  printk ("in cleanup module simple\n");
}

module_init(init_simple);
module_exit(cleanup_simple);

