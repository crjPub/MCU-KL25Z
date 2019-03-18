# 准备工作
## 安装MCUXpresso IDE
首先需要安装MCUXpresso IDE集成开发环境，下载MCUXpresso IDE集成开发环境先注册nxp账号[<u>下载MCUXpresso Integrated Development Environment(IDE)</u>](https://www.nxp.com/support/developer-resources/software-development-tools/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE)，安装过程按照安装包安装流程进行，详细安装过程略。
## 下载SDK
选择开发板对应的SDK开发包，前往[NXP下载页](https://mcuxpresso.nxp.com/en/select)，搜索相应的开发板名称，并选择**Build MCUXpresso SDK**即可下载相应SDK压缩包。
![download SDK](https://github.com/crjPub/MCU-KL25Z/blob/master/download%20SDK.png)
## 导入SDK
打开IDE，将下载好的SDK拖入右下角的**Installed SDKs**即可完成导入SDK。
![IDE](https://i.imgur.com/P4BUHae.png)
## 创建一个SDK Example
在IDE主界面的左下角的**Quickstart Panel**中选择**Import SDK examples(s)...**，如果只安装了对应的那一个SDK，双击即可。
![examples](https://i.imgur.com/Ufz6jon.png)

只需选择相应的示例，例如下面选择*driver_examples/gpio/led_output*。
![](https://i.imgur.com/x0IFEDY.png)

注意连接的端口，有两个，USB要连接下图端口，正确连接，STATUS LED会常亮绿灯。
![](https://i.imgur.com/zu98DBY.jpg)
点击Build可以编译程序，无报错且连接正确后，可以点击Debug调试程序。
![](https://i.imgur.com/Hvfh1TD.png)
