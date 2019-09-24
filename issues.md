# 问题及解决汇总

Problem：在gpio_led_output的demo中，在程序中修改没有实现LED颜色变化的功能    
Solution：原因在于没有修改demo的配置文件。除了主程序中要修改并添加相应的LED灯的GPIO端口组和相应引脚，还必须要修改LED灯引脚配置文件，不然默认的初始化函数不会初始化引脚。  

Problem：UART模块的demo不能收发
UART有三个分别为UART0、UART1、UART2根据demo的readme.txt貌似UART1和UART2要改变接线（硬件层面的改变？），板子上也没有跳帽之类的，不懂。目前只能使用UART0。

改变debug方式  
MCUXpresso IDE 三种调试方式：LinkServer Debug、P&E Debug、SEGGER Debug。  
Note: LinkServer advanced features such as Power Measurement, Live Global Variables etc. will
not be available via a P&E debug connection.   
推荐LinkServer Debug 由上述可知，实时变量监控只有这种调试方式有。
需要改变调试方式要重置开发板然后重新烧入驱动程序。

具体操作是 按住reset键，插入USB，进入bootloader模式，此时设备被识别为一个盘符为BOOTLOADER的可移动硬盘，然后将固件程序复制到此盘中即可。然后拔下USB，再插入（不要按住reset），此时进入Debug模式。若是使用MSD固件，则会进入MSD模式，此时设备被识别为盘符为FRDM-KL25Z的硬盘。
  
  
编程时，如何快速的查找所有的功能函数？类似PE中罗列函数？

宏定义时，如何确定宏名称？

