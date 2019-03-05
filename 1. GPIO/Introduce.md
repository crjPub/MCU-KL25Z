# GPIO

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
Initializes a GPIO pin used by the board.
初始化函数原型
```
void GPIO_PinInit (GPIO_Type* base, uint32_t pin, const gpio_pin_config_t* config)	
```
`base`为GPIO端口组，如GPIOA, GPIOB, GPIOC  
`pin`为端口组下的引脚号  
`config`GPIO引脚配置  

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
