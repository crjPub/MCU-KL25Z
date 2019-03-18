# PIT —— Periodic Interrupt Timer
## 介绍
PIT周期中断计时器，计时到预设数值产生中断。相比在主函数中使用delay()函数的方法，使用中断占用的CPU资源较少，下面就SDK Example中PIT中断示例进行简单分析。  

## API
### 数据类型
`struct pit_config_t`  
> This structure holds the configuration settings for the PIT peripheral.   
可以利用函数`PIT_GetDefaultConfig()`配置默认参数，指针类型的`pit_config_t`作为函数的参数。例：'PIT_GetDefaultConfig(&pitConfig)'; 

`enum pit_chnl_t`  
枚举类型，表示不同的channel，`kPIT_Chnl_0`表示channel0，还可以用123.  
NOTE:**实际可用信道数取决于SOC**  

`enum pit_interrupt_enable_t`  
枚举类型，`kPIT_TimerInterruptEnable`表示计时中断使能

`enum pit_status_flags_t`  
枚举类型，`kPIT_TimerFlag` Timer flag.  

### 获取配置信息
> gets the default configurations

```
static void PIT_GetDefaultConfig(pit_config_t* config)
```
`config`	Pointer to the user's PIT config structure

```
pit_config_t pitConfig;    //Structure of initialize PIT
PIT_GetDefaultConfig(&pitConfig);
```

### 初始化
> initializes the PIT with specified configurations


```
void PIT_Init(PIT_Type* base, const pit_config_t* config)
```
`base`	PIT peripheral base address

NOTE:**This API should be called at the beginning of the application using the PIT driver.**

### 设置周期
```
static void PIT_SetTimerPeriod(PIT_Type* base, pit_chnl_t channel, uint32_t count)
```  
`base` PIT peripheral base address  
`channel` Timer channel number  
`count` Timer period in units of ticks  
计时器从该函数设置的值开始计数，直到它达到0，然后产生一个中断并从寄存器加载该值。将新值写入此寄存器不会立即重新启动计时器，而是当目前计时完成时再改变。
例：`PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(1000000U, PIT_SOURCE_CLOCK))`;

### 使能中断
```
static void PIT_EnableInterrupts(PIT_Type* base, pit_chnl_t channel, uint32_t mask)
```  
`base` PIT peripheral base address
`channel` channel Timer channel number
`mask` The interrupts to enable. This is a logical OR of members of the enumeration ::pit_interrupt_enable_t

### 开始时钟计数
```
static inline void PIT_StartTimer(PIT_Type *base, pit_chnl_t channel)
```
`base`  PIT peripheral base address
`channel`  Timer channel number.
