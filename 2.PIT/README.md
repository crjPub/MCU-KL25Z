# PIT —— Periodic Interrupt Timer
## 介绍
PIT周期中断计时器，计时到预设数值产生中断。相比在主函数中使用delay()函数的方法，使用中断占用的CPU资源较少，下面就SDK Example中PIT中断示例进行简单分析。  

### Initialization and deinitialization
[`PIT_Init()`](#func1) 使用指定的配置初始化PIT模块。  
[`PIT_GetDefaultConfig()`](#func2) 获取默认配置。  
[`PIT_SetTimerChainMode()`](#func3) 配置PIT通道为级联模式。  
[`PIT_Deinit()`](#func4) 禁用PIT计时器并禁用模块时钟。  

### Read and Write the timer period
[`PIT_SetTimerPeriod()`](#func5) 以计数单位设置计时器周期。计时器从该函数设置的值开始向下计数，直到它达到0。  
[`PIT_GetCurrentTimerCount()`](#func6) 读取当前计时器计数值。此函数返回从0到计时器初始值范围内的计数值。  
注意：计数器周期操作函数采用以刻度为单位的计数值。可以调用fsl_common.h中提供的实用程序宏来转换为微秒或毫秒。  

### Timer Start and Stop
[`PIT_StartTimer()`](#func7) 启动计时器计数。调用此函数后，计时器载入[`PITR_SetTimerPeriod()`](#func5)设置的起始值。当计数器到达0后，生成一个触发脉冲并设置超时中断标志。  
[`PIT_StopTimer()`](#func8) 停止计时器计数。  

### Interrupt Interface
[`PIT_EnableInterrupts()`](#func9) 选中的PIT模块中断启用。  
[`PIT_DisableInterrupts()`](#func10)选中的PIT模块中断禁用。  
[`PIT_GetEnabledInterrupts()`](#func11) 获取使能的PIT通道。  

### Status Interface
[`PIT_GetStatusFlags()`](#func12) 获取PIT状态标志。   
[`PIT_ClearStatusFlags()`](#func13) 清楚PIT状态标志。  

### Useful Function
`USEC_TO_COUNT(us, clockFreqInHz)` 把微秒转换为ticks。  

## 功能函数
### <span id="func1">初始化PIT</span>

	void PIT_Init(PIT_Type* base, const pit_config_t* config)

`base`：PIT外设基址。  
`config`：[`pit_config_t`](#struct1)类型指针，用于PIT配置。  

**NOTE:This API should be called at the beginning of the application using the PIT driver.**

### <span id="func2">默认配置</span>

	static void PIT_GetDefaultConfig(pit_config_t* config)

默认配置为`config->enableRunInDebug = false;`  

### <span id="func3">级联计时器</span>

	static void PIT_SetTimerChainMode(PIT_Type* base, pit_chnl_t channel, bool enable)

`channel`：[`pit_chnl_t`](#enum1)类型，与前一个计时器级联的计时器通道。  
`enable`：当前计时器是否级联到前一个计时器。  

当计时器启用了级联模式时，它只在上一个计时器过期后计数。如果计时器n-1已倒计时到0，则计数器n将该值递减1。每个计时器都是32位的，将计时器级联在一起，形成一个更长的计时器（64位及更大）。第一个计时器（计时器0）不能链接到任何其他计时器。  

### <span id="func4">禁用PIT</span>
 
	void PIT_Deinit(PIT_Type* base)

### <span id="func5">设置计时周期</span>

	static void PIT_SetTimerPeriod(PIT_Type* base, pit_chnl_t channel, uint32_t count)

`count`：以一个时钟周期为单位的计数个数。  
计时器从该函数设置的值开始计数，直到它达到0，然后它生成一个中断并再次加载该寄存器值。将新值写入此寄存器不会立刻重新启动计时器。相反，该值在计时器本次计时结束后加载。  

**NOTE：Users can call the utility macros provided in fsl_common.h to convert to ticks.**  

### <span id="func6">获取当前计数值</span>

	static uint32_t PIT_GetCurrentTimerCount(PIT_Type* base, pit_chnl_t channel)

### <span id="func7">开始计数器</span>

	static void PIT_StartTimer(PIT_Type* base, pit_chnl_t channel)

调用此函数后，计时器加载初始值，倒计时到0，然后再次加载各自的起始值。每次计时器达到0，它都会生成一个触发脉冲并设置超时中断标志。  

### <span id="func8">停止计数器</span>

	static void PIT_StopTimer(PIT_Type* base, pit_chnl_t channel)

### <span id="func9">启用中断</span>

	static void PIT_EnableInterrupts(PIT_Type* base, pit_chnl_t 	channel,  uint32_t mask)	

`mask`：需要使能的中断。是枚举类型[`pit_interrupt_enable_t`](#enum2)成员的逻辑或。  

### <span id="func10">禁用中断</span>

	static void PIT_DisableInterrupts(PIT_Type* base, pit_chnl_t channel, uint32_t mask)

`mask`：需要禁用的中断。是枚举类型[`pit_interrupt_enable_t`](#enum2)成员的逻辑或。  
### <span id="func11">获取中断</span>

	static uint32_t PIT_GetStatusFlags(PIT_Type* base, pit_chnl_t channel)

### <span id="func12">获取状态</span>

	static uint32_t PIT_GetStatusFlags(PIT_Type* base, pit_chnl_t channel)

### <span id="func13">清除状态</span>

	static void PIT_ClearStatusFlags(PIT_Type* base, pit_chnl_t channel, uint32_t mask)

`mask`：需要清除的标志位。是枚举类型[`pit_status_flags_t`](#enum3)成员的逻辑或。  


## 数据类型
### <span id="struct1">`struct pit_config_t`</span>   
PIT外设配置设置，可以利用函数`PIT_GetDefaultConfig()`配置默认参数。

参数表  

参数名称|类型|说明
-|-|-
enableRunInDebug|`bool`|计时器工作在调试模式

## 枚举类型
### <span id="enum1">`pit_chnl_t`</span>
PIT通道

值|说明
-|-
kPIT_Chnl_0|PIT channel number 0.
kPIT_Chnl_1|PIT channel number 1.
kPIT_Chnl_2|PIT channel number 2.
kPIT_Chnl_3|PIT channel number 3.

### <span id="enum2">`pit_interrupt_enable_t`</span>
值|说明
-|-
kPIT_TimerInterruptEnable|Timer interrupt enable.


### <span id="enum3">`pit_status_flags_t`</span>
值|说明
-|-
kPIT_TimerFlag|Timer flag.
