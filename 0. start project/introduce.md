# 准备工作
## 安装IDE
首先需要安装集成开发环境，[<u>下载MCUXpresso Integrated Development Environment(IDE)</u>](https://www.nxp.com/support/developer-resources/software-development-tools/mcuxpresso-software-and-tools/mcuxpresso-integrated-development-environment-ide:MCUXpresso-IDE)，过程略。
## 下载SDK
其次选择开发板对应的SDK开发包，前往[NXP下载页](https://mcuxpresso.nxp.com/en/select)，搜索开发板名称，并选择**Build MCUXpresso SDK**即可下载SDK压缩包。
![download SDK](https://i.imgur.com/OkR0AHx.png)
## 导入SDK
打开IDE，将下载好的SDK拖入右下角的**Installed SDKs**即可完成导入SDK。
![IDE](https://i.imgur.com/P4BUHae.png)
## 创建一个SDK Example
在IDE主界面的左下角的**Quickstart Panel**中选择**Import SDK examples(s)...**，如果只安装了对应的那一个SDK，双击即可。
![examples](https://i.imgur.com/Ufz6jon.png)

只需选择相应的示例，例如下面选择*driver_examples/gpio/led_output*。
![](https://i.imgur.com/x0IFEDY.png)
