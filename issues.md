# 问题及解决汇总

Problem：在gpio_led_output的demo中，在程序中修改没有实现LED颜色改变的功能
Solution：原因在于没有修改demo的配置文件，除了主程序要修改，还必须要修改引脚配置文件，不然默认的初始化函数不会初始化引脚。

