#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#include <mach/gpio.h>
#include <mach/regs-gpio.h>
#include <plat/gpio-cfg.h>
#include <asm/uaccess.h>

static int major = 200;
#define DEVICE_NAME "baodev"

// volatile unsigned long *GPH0CON=NULL;
// volatile unsigned long *GPH0DAT=NULL;
// volatile unsigned long *GPD1CON=NULL;
// volatile unsigned long *GPD1DAT=NULL;



static int boil_gpios[] = {
	S5PV210_GPH2(0),
	S5PV210_GPH2(1),
	S5PV210_GPH2(2),
	S5PV210_GPH2(3),
	S5PV210_GPH3(0),
	S5PV210_GPH3(1),
	S5PV210_GPH3(2),
	S5PV210_GPH3(3),
};



static int baodev_open(struct inode *inode,struct file *file){
	
	int ret=0;
	int i;
	printk("baodev_open\n");

	// *GPH0CON &= 0xffff0000;
	// *GPH0CON |= 0x1111;
	// *GPH0DAT &=0xf8;
	// *GPD1CON &=0x00fff0;
	// *GPD1CON |=0x110001;
	// *GPD1DAT &=0x0;
	// printk("%x:%x:%x:%x",*GPH0CON,*GPH0DAT,*GPD1CON,*GPD1DAT);


	for (i = 0; i < 8; i++) {
		ret = gpio_request(boil_gpios[i], "baodev");
		if (ret) {
			printk("%s: request GPIO %d for baodev failed, ret = %d\n", DEVICE_NAME,
					boil_gpios[i], ret);
			return returnet;
		}

		s3c_gpio_cfgpin(boil_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(boil_gpios[i], 0);
	}



	return 0;
}


// static int baodev_open(struct inode *inode,struct file *file){
// 	printk("baodev_open\n");
// 	*GPH0CON &= 0xffff0000;
// 	*GPH0CON |= 0x1111;
// 	*GPH0DAT &=0xf8;
// 	*GPD1CON &=0x00fff0;
// 	*GPD1CON |=0x110001;
// 	*GPD1DAT &=0x0;
// 	printk("%x:%x:%x:%x",*GPH0CON,*GPH0DAT,*GPD1CON,*GPD1DAT);

// 	return 0;
// }

static int baodev_write(struct file* file,const char __user *buf,size_t count,loff_t * loff){
	
	int tmp,i,j,k,flag=-1;

	char data;
	// for(i=0;i<8;i++){
	// 	gpio_set_value(boil_gpios[i],0);
	// }
	printk("baodev_write\n");

	tmp=copy_from_user(&data,buf,1);
	if(tmp!=0){
		printk("baodev_write fail\n");
	}
	if(data=='1'){
		printk("baowen\n");
		for(i=0;i<8;i++){
			if(i==(int)(data-49)){
				// gpio_set_value(boil_gpios[i],1);
				flag=i;
			}else{
				gpio_set_value(boil_gpios[i],0);
			}
			
			printk("%x <>",gpio_get_value(boil_gpios[i]));	
		}
		gpio_set_value(boil_gpios[flag],1);
			printk("\n");
		for(i=0;i<8;i++){
			printk("%x <>",gpio_get_value(boil_gpios[i]));
		}
		// k=0x1000000;
		// j=k;
		// while(k--){
		// 	while(j--);
		// }
		// printk("<><>987654");
		// gpio_set_value(boil_gpios[flag],0);
		//*GPH0DAT &=0xf8;()
		// gpio_set_value(boil_gpios[2],1);
		// gpio_set_value(boil_gpios[1],0);
		// gpio_set_value(boil_gpios[0],0);
		
			
		//printk("%x<>\n",*GPH0DAT);
		//*GPH0DAT |=0x4;
		//printk("%x<>\n",*GPH0DAT);
		//*GPH0DAT &=0xfe;

		//printk("%x<>\n",*GPH0DAT);
	}
	else if(data=='2'){
		// printk("baotang\n");
		// gpio_set_value(boil_gpios[2],1);
		// gpio_set_value(boil_gpios[1],0);
		// gpio_set_value(boil_gpios[0],1);
		// printk("%x <>",gpio_get_value(boil_gpios[1]));
		for(i=0;i<8;i++){
			if(i==(int)(data-49)){
				// gpio_set_value(boil_gpios[i],1);
				flag=i;
			}else{
				gpio_set_value(boil_gpios[i],0);
			}

			printk("%x <>",gpio_get_value(boil_gpios[i]));	
		}
		gpio_set_value(boil_gpios[flag],1);
			printk("\n");
		for(i=0;i<8;i++){
			printk("%x <>",gpio_get_value(boil_gpios[i]));
		}
		// k=0x1000000;
		// j=k;
		// while(k--){
		// 	while(j--);
		// }
		// printk("<><>987654");
		// gpio_set_value(boil_gpios[flag],0);
		// *GPH0DAT &=0xf8;
		// printk("%x<>\n",*GPH0DAT);
		// *GPH0DAT |=0x5;
		// printk("%x:%x",*GPH0DAT);
	}
	else if(data=='3'){
		// printk("rouji\n");
		// gpio_set_value(boil_gpios[2],1);
		// gpio_set_value(boil_gpios[1],1);
		// gpio_set_value(boil_gpios[0],0);
		// printk("%x <>",gpio_get_value(boil_gpios[2]));
		for(i=0;i<8;i++){
			if(i==(int)(data-49)){
				flag=i;
			}else{
				gpio_set_value(boil_gpios[i],0);
			}
			printk("%x <>",gpio_get_value(boil_gpios[i]));	
		}
		gpio_set_value(boil_gpios[flag],1);
			printk("\n");
		for(i=0;i<8;i++){
			printk("%x <>",gpio_get_value(boil_gpios[i]));
		}
		// k=0x1000000;
		// j=k;
		// while(k--){
		// 	while(j--);
		// }
		// printk("<><>987654");
		// gpio_set_value(boil_gpios[flag],0);
		// *GPH0DAT &=0xf8;
		// printk("%x<>\n",*GPH0DAT);
		// *GPH0DAT |=0x6;
		// printk("%x<>\n",*GPH0DAT);
		// *GPH0DAT &=0xfe;
		// printk("%x:%x",*GPH0DAT);
	}else if(data=='4'){
		// printk("doutijing\n");
		// gpio_set_value(boil_gpios[2],1);
		// gpio_set_value(boil_gpios[1],1);
		// gpio_set_value(boil_gpios[0],1);
		for(i=0;i<8;i++){
			if(i==(int)(data-49)){
				flag=i;
			}else{
				gpio_set_value(boil_gpios[i],0);
			}
			printk("%x <>",gpio_get_value(boil_gpios[i]));	
		}
		gpio_set_value(boil_gpios[flag],1);
		printk("\n");
		for(i=0;i<8;i++){
			printk("%x <>",gpio_get_value(boil_gpios[i]));
		}
		// k=0x1000000;
		// j=k;
		// while(k--){
		// 	while(j--);
		// }
		// printk("<><>987654");
		// gpio_set_value(boil_gpios[flag],0);
		// *GPH0DAT &=0xf8;
		// printk("%x<>\n",*GPH0DAT);
		// *GPH0DAT |=0x7;
		// 	printk("%x:%x",*GPH0DAT);
	}
	 else if(data=='5'){
	 	printk("heihei");
	 	for(i=0;i<8;i++){
			if(i==(int)(data-49)){
				flag=i;
			}else{
				gpio_set_value(boil_gpios[i],0);
			}
			printk("%x <>",gpio_get_value(boil_gpios[i]));	
		}
		gpio_set_value(boil_gpios[flag],1);
		printk("\n");
		for(i=0;i<8;i++){
			printk("%x <>",gpio_get_value(boil_gpios[i]));
		}
		
	// 	*GPD1DAT &=0x2e;
	// 	printk("%x:%x",*GPD1DAT,*GPH1DAT);
	  //}
	  //else if(data=='6'){
	//  	printk("yuyue\n");
	// 	for(i=0;i<8;i++){
	// 		if(i==(int)(data-49)){
	// 			gpio_set_value(boil_gpios[i],1);
	// 		}else{
	// 			gpio_set_value(boil_gpios[i],0);
	// 		}
	// 		printk("%x <>",gpio_get_value(boil_gpios[i]));	
	// 	}
	// // 	*GPD1DAT &=0x2f;
	// // 	printk("%x:%x",*GPD1DAT,*GPH1DAT);
	// 	}else if(data=='7'){
	// 	printk("jiangwen\n");
	// 	for(i=0;i<8;i++){
	// 		if(i==(int)(data-49)){
	// 			gpio_set_value(boil_gpios[i],1);
	// 		}else{
	// 			gpio_set_value(boil_gpios[i],0);
	// 		}
	// 		printk("%x <>",gpio_get_value(boil_gpios[i]));	
	// 	}
	// // 	*GPD1DAT &=0x3e;
	// 	}else if(data=='8'){
	// 	printk("baoyashijian\n");
	// 	for(i=0;i<8;i++){
	// 		if(i==(int)(data-49)){
	// 			gpio_set_value(boil_gpios[i],1);
	// 		}else{
	// 			gpio_set_value(boil_gpios[i],0);
	// 		}
	// 		printk("%x <>",gpio_get_value(boil_gpios[i]));	
	// 	}
	// // 	*GPD1DAT &=0x3f;
	  }else if(data=='6'){
		printk("fuwei\n");
		for(i=0;i<8;i++){
	 	gpio_set_value(boil_gpios[i],0);
	 }
		// *GPH1DAT &=0x3f;
		// *GPD1DAT &=0xf;
	}//else if(data=='0'){
	// 	printk("zhufan\n");
	// 	*GPH1DAT &=0x7f;
	// 	*GPD1DAT &=0xf;
	// }else if(data=='a'){
	// 	printk("xifan\n");
	// 	*GPH1DAT &=0x3f;
	// 	*GPD1DAT &=0x2f;
	// }else if(data=='b'){
	// 	printk("zhougeng\n");
	// 	*GPH1DAT &=0x7f;
	// 	*GPD1DAT &=0x2f;
	// }else if(data=='c'){
	// 	printk("yuanweidun\n");
	// 	*GPH1DAT &=0x3f;
	// 	*GPD1DAT &=0x1f;
	// }else if(data=='d'){
	// 	printk("qinxiangmen\n");
	// 	*GPH1DAT &=0x7f;
	// 	*GPD1DAT &=0x1f;
	// }else if(data=='e'){
	// 	printk("kougan\n");
	// 	*GPH1DAT &=0x3f;
	// 	*GPD1DAT &=0x3f;
	// }
		else{
		printk("pangzijiawawahendiaode");
	}
	return 0;
}

static struct file_operations baodev_ops=
{
	.owner =THIS_MODULE,
	.open=baodev_open,
	.write=baodev_write,	
};

// static struct file_operations baodev_ops = {
// 	.owner			= THIS_MODULE,
// 	.open=baodev_open,
// 	.write=baodev_write,
// };

// static struct miscdevice mini210_led_dev = {
// 	.minor			= MISC_DYNAMIC_MINOR,
// 	.name			= DEVICE_NAME,
// 	.fops			= &baodev_ops,
// };

static int __init baodev_init(void){
	printk("baodev_init\n");
	int ret=register_chrdev(major,"baodev",&baodev_ops);

	return 0;
}

static void __exit baodev_exit(void){
	
	int i;
	printk("baodev_exit\n");
	for (i = 0; i < 8; i++) {
		gpio_free(boil_gpios[i]);
	}
	unregister_chrdev(major,"baodev");
	return;
}

module_init(baodev_init);
module_exit(baodev_exit);

MODULE_LICENSE("GPL");
