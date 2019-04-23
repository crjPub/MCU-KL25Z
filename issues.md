# 问题及解决汇总

Problem：在gpio_led_output的demo中，在程序中修改没有实现LED颜色变化的功能    
Solution：原因在于没有修改demo的配置文件。除了主程序中要修改并添加相应的LED灯的GPIO端口组和相应引脚，还必须要修改LED灯引脚配置文件，不然默认的初始化函数不会初始化引脚。  

Problem：UART模块的demo不能收发
UART有三个分别为UART0、UART1、UART2根据demo的readme.txt貌似UART1和UART2要改变接线（硬件层面的改变？），板子上也没有跳帽之类的，不懂。目前只能使用UART0。
