# GPIO —— General Purpose Input/Output Driver

## 介绍
MCUXpresso SDK为设备的通用输入/输出模块提供外设驱动程序提供。  

### GPIO Configuration
[`GPIO_PinInit`](#func1)为开发板使用的引脚初始化。  

### GPIO Output Operations
[`GPIO_WritePinOutput`](#func2)设置GPIO的输出为0或1。  
[`GPIO_SetPinsOutput`](#func3)设置GPIO的输出为1，即置位。  
[`GPIO_ClearPinsOutput`](#func4)设置GPIO的输出为0，即复位。  
[`GPIO_TogglePinsOutput`](#func5)将GPIO的输出反转。  

### GPIO Input Operations
[`GPIO_ReadPinInput`](#func6)读取GPIO的输入值。  

### GPIO Interrupt
[`GPIO_GetPinsInterruptFlags`](#func7)读取GPIO端口中断状态标志。  
[`GPIO_ClearPinsInterruptFlags`](#func8)清除GPIO中断状态标志。  

## 功能函数
### <span id="func1">初始化</span>

	void GPIO_PinInit(GPIO_Type* base, uint32_t pin, const gpio_pin_config_t* config)

`base`：GPIO外设基址，即端口组，如GPIOA, GPIOB, GPIOC。   
`pin`：端口组下的引脚号。  
`config`：[`gpio_pin_config_t`](#struct1)类型的引脚配置。

### <span id="func2">写输出</span>

	static void GPIO_WritePinOutput(GPIO_Type* base, uint32_t pin, uint8_t output)

`output`：GPIO输出逻辑。0对应输出低电平；1对应输出高电平。  

### <span id="func3">输出置位</span>
	
	static void GPIO_SetPinsOutput(GPIO_Type* base, uint32_t mask)

`mask`：GPIO引脚宏。


### <span id="func4">输出复位</span>

	static void GPIO_ClearPinsOutput(GPIO_Type* base, uint32_t mask)

### <span id="func5">输出翻转</span>

	static void GPIO_TogglePinsOutput(GPIO_Type* base, uint32_t mask)

### <span id="func6">读输入</span>

	static uint32_t GPIO_ReadPinInput(GPIO_Type* base, uint32_t pin)

返回值为0或1，对应低或高电平逻辑。

### <span id="func7">获取中断标志</span>

	uint32_t GPIO_GetPinsInterruptFlags(GPIO_Type* base)

如果引脚被配置为产生DMA请求，相应的标志位在请求完成后自动清除。否则标志位一直保持到逻辑高电平写入此位。
### <span id="func8">清除中断标志</span>

	void GPIO_ClearPinsInterruptFlags(GPIO_Type* base, uint32_t mask)


## 数据结构
### <span id="struct1">`gpio_pin_config_t`</span>
每一个引脚只能配置为输入或者输出，如果配置为输入，参数outputLogic不需使用。

参数表  

参数名称|类型|说明
-|-|-
pinDirection|[`gpio_pin_direction_t`](#enum1)|GPIO方向，输入或输出
outputLogic|`uint8_t`|默认输出电平


## 枚举类型
### <span id="enum1">`gpio_pin_direction_t`</span>
值|说明
-|-
kGPIO_DigitalInput|设置引脚为数字输入
kGPIO_DigitalOutput|设置引脚为数字输出	



# 硬件配置
首先需要配置引脚。
点击菜单栏右侧的引脚*Pins*
![pins](https://i.imgur.com/aejMMki.png)
出现的即为配置引脚的可视化界面  
![main view](https://i.imgur.com/uopsZBo.png)
首先在复选框1处选择项目，程序会给出项目对应的开发板引脚图，左侧勾选出需要使用的引脚，会在下方出现初始化的配置信息，根据需要修改即可，程序会实时地在右侧生成对应的配置代码，配置完成后，点击2处的更新工程，则程序会修改项目的代码。如果不配置硬件，则不能实现对应功能。  
注：MUCXPresso Config Tools也有同样的功能，但是IDE集成了这些工具，不用再下载CFG程序。  

## RGB LED
控制RGB LED灯
每个Pin（针脚）一次只能配置为输入或者输出
```
struct gpio_pin_config_t = {gpio_pin_direction_t pinDirection, uint8_t outputLogic}
```
`pinDirection`为枚举类型，数字输入为`kGPIO_DigitalInput`，数字输出为`kGPIO_DigitalOutput`  
`outputLogic`设置默认的输出电平，可以为`0`或`1`.对于输出没意义  
下面配置为默认为低电平的输出端口
```
gpio_pin_config_t led_config = {
  kGPIO_DigitalOutput, 0,
};
```


使用示例
```
GPIO_SetPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
GPIO_ClearPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
GPIO_TogglePinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
```

# 总结
使用GPIO的步骤可以概括为：配置引脚->引入配置文件->初始化引脚->使用GPIO函数

