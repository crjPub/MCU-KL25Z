# GPIO

## 硬件配置
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

## GPIO Configuration
### 端口初始化 
> Initializes a GPIO pin used by the board.
初始化函数原型
```
void GPIO_PinInit (GPIO_Type* base, uint32_t pin, const gpio_pin_config_t* config)	
```
`base`为GPIO端口组，如GPIOA, GPIOB, GPIOC  
`pin`为端口组下的引脚号  
`config`GPIO引脚配置  
配置示例
```
GPIO_PinInit(BOARD_LED_GPIO, BOARD_LED_GPIO_PIN, &led_config);
```

## GPIO Output Operations
### 端口写入
> Sets the output level of the multiple GPIO pins to the logic 1 or 0.
```
static void GPIO_WritePinOutput (GPIO_Type *base, uint32_t pin, uint8_t output)
```
### 端口置位
> Sets the output level of the multiple GPIO pins to the logic 1. 
```
static void GPIO_SetPinsOutput (GPIO_Type *base, uint32_t mask)
```
### 端口复位
> Sets the output level of the multiple GPIO pins to the logic 0.
```
static void GPIO_ClearPinsOutput (GPIO_Type *base, uint32_t mask)
```
### 端口反转
> Reverses the current output logic of the multiple GPIO pins.
```
static void GPIO_TogglePinsOutput (GPIO_Type *base, uint32_t mask)
```

使用示例
```
GPIO_SetPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
GPIO_ClearPinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
GPIO_TogglePinsOutput(BOARD_LED_GPIO, 1u << BOARD_LED_GPIO_PIN);
```
## 总结
使用GPIO的步骤可以概括为：配置引脚->引入配置文件->初始化引脚->使用GPIO函数

