MCUXpresso SDK为设备的定时器PWM模块（TPM）提供驱动程序。TPM驱动程序支持生成PWM信号、输入捕获和输出比较模式。   
函数[`TPM_Init()`](#func1)使用指定的配置初始化TPM。  
函数[`TPM_GetDefaultConfig()`](#func2)获取默认配置信息。  
函数[`TPM_Deinit()`](#func3)禁用TPM计数器并关闭模块时钟。  
函数[`TPM_SetupPwm()`](#func4)为PWM输出设置TPM通道，该功能可以为多个通道设置PWM信号属性。每个通道都有自己的[`tpm_chnl_pwm_signal_param_t`](#struct1)结构，用于指定输出信号的占空比和电平模式。然而，相同的脉宽调制周期和脉宽调制模式适用于所有请求脉宽调制输出的信道。信号占空比以脉宽调制周期的百分比提供。其值应介于0和100之间，其中0为非激活信号（0%占空比）和100为始终激活信号（100%占空比）。当产生组合的脉宽调制信号时，所传递的信道号是指信道对号，例如0是指信道0和1，1是指信道2和3。  
函数[`TPM_UpdatePwmDutycycle()`](#func5)更新特定TPM通道的脉宽调制信号占空比。    
函数[`TPM_UpdateChnlEdgeLevelSelect()`](#func6)更新特定TPM通道的级别选择位。这可用于在更改PWM信号时禁用PWM输出。  
函数[`TPM_SetupInputCapture()`](#func7)为输入捕获设置一个TPM通道，用户可以指定捕获边缘。  

函数[`TPM_StartTimer()`](#func8)

## 功能函数  

<span id="func1">初始化函数</span>

	void TPM_Init(TPM_Type* base, const tpm_config_t* config)

`base`：TPM外设基址  
`config`：指向用户配置类型[`tpm_config_t`](#struct2)指针  
注意：此函数应该在TPM驱动器使用开始时使用。  

<span id="func2">获取默认配置</span>

	void TPM_GetDefaultConfig(tpm_config_t* config)

`config`：指向用户配置类型[`tpm_config_t`](#struct2)指针  
默认配置为

	config->prescale = kTPM_Prescale_Divide_1;
	config->useGlobalTimeBase = false;
	config->dozeEnable = false;
	config->dbgMode = false;
	config->enableReloadOnTrigger = false;
	config->enableStopOnOverflow = false;
	config->enableStartOnTrigger = false;
	#if FSL_FEATURE_TPM_HAS_PAUSE_COUNTER_ON_TRIGGER
		config->enablePauseOnTrigger = false;
	#endif
	config->triggerSelect = kTPM_Trigger_Select_0;
	#if FSL_FEATURE_TPM_HAS_EXTERNAL_TRIGGER_SELECTION
		config->triggerSource = kTPM_TriggerSource_External;
	#endif

<span id="func3">禁用TPM</span>
	void TPM_Deinit(TPM_Type* base)

`base`：TPM外设基址   

<span id="func4">PWM设置</span>
	status_t TPM_SetupPwm(TPM_Type* base,const tpm_chnl_pwm_signal_param_t* chnlParams, uint8_t numOfChnls, tpm_pwm_mode_t mode, uint32_t pwmFreq_Hz, uint32_t srcClock_Hz)

`base`：TPM外设基址   
`chnlParams`：配置通道的PWM通道参数数组   
`numOfChnls`：要配置的通道数，应为传入数组的大小    
`mode`：脉宽调制操作模式，可选项在枚举类型[`tpm_pwm_mode_t`](#enum4)  
`pwmFreq_Hz`：脉宽调制信号频率（Hz）  
`srcClock_Hz`：以赫兹为单位的TPM计数器时钟  

调用此函数来配置脉宽调制信号周期、模式、周期和边缘。使用此功能配置将用于输出PWM信号的所有TPM通道。

<span id="func5">更新PWM设置</span>

	void TPM_UpdatePwmDutycycle(TPM_Type* base, tpm_chnl_t 	chnlNumber, tpm_pwm_mode_t currentPwmMode, uint8_t dutyCyclePercent)

`base`：TPM外设基址   
`chnlNumber`：[`tpm_chnl_t`](#enum2)类型通道号，在组合模式下，表示通道对号（如0，2，4）  
`currentPwmMode`：在脉宽调制设置期间设置的当前脉宽调制模式，可选项在枚举类型[`tpm_pwm_mode_t`](#enum4)  
`dutyCyclePercent`：新的脉宽调制脉冲宽度，值应在0到100之间0=非激活信号（0%占空比）100=激活信号（100%占空比）

<span id="func6"></span>
	
	void TPM_UpdateChnlEdgeLevelSelect(TPM_Type* base, tpm_chnl_t chnlNumber, uint8_t level)

`base`：TPM外设基址   
`chnlNumber`：[`tpm_chnl_t`](#enum2)类型通道号，在组合模式下，表示通道对号（如0，2，4）  
`level`：The level to be set to the ELSnB:ELSnA field; valid values are 00, 01, 10, 11. See the appropriate SoC reference 

<span id="func8"></span>

	static void TPM_StartTimer(TPM_Type* base, tpm_clock_source_t clockSource)

`base`：TPM外设基址   
`clockSource`：[`tpm_clock_source_t`](#enum5)类型TPM时钟源，一旦设置了时钟源，计数器将开始运行。


## 数据结构
<span id="struct1"></span>

	struct tpm_chnl_pwm_signal_param_t

参数表  

参数名称|类型|说明
-|-|-
chnlNumber|[tpm_chnl_t](#enum2)|要配置的TPM通道
level|[tpm_pwm_level_select_t](#enum3)|脉宽调制输出激活电平选择
dutyCyclePercent|uint8_t|脉宽调制脉冲宽度，值应在0到100之间

<span id="struct2"></span>

	struct tpm_config_t

参数表  

参数名称|类型|说明
-|-|-
prescale|[tpm_clock_prescale_t](#enum1)|TPM时钟预定值
useGlobalTimeBase|bool|true：使用外部时钟
triggerSelect|tpm_trigger_select_t|用于控制计数器操作的输入触发器
enableDoze|bool|true：TPM计数器在休眠模式下暂停
enableDebugMode|bool|true：TPM计数器继续处于调试模式
enableReloadOnTrigger|bool|TPM计数器在触发器上重新加载
enableStopOnOverflow|bool|溢出后TPM计数器停止
enableStartOnTrigger|bool|仅当检测到触发器时，才会启动TPM计数器

## 枚举类型
<span id="enum1"></span>

	enum tpm_clock_prescale_t

值|说明
-|-
kTPM_Prescale_Divide_1|Divide by 1.
kTPM_Prescale_Divide_2|Divide by 2.
kTPM_Prescale_Divide_4|Divide by 4.
kTPM_Prescale_Divide_8|Divide by 8.
kTPM_Prescale_Divide_16|Divide by 16.
kTPM_Prescale_Divide_32|Divide by 32.
kTPM_Prescale_Divide_64|Divide by 64.
kTPM_Prescale_Divide_128|Divide by 128.

<span id="enum2"></span>

	enum tpm_chnl_t

值|说明
-|-
kTPM_Chnl_0|TPM channel number 0.
kTPM_Chnl_1|TPM channel number 1.
kTPM_Chnl_2|TPM channel number 2.
kTPM_Chnl_3|TPM channel number 3.
kTPM_Chnl_4|TPM channel number 4.
kTPM_Chnl_5|TPM channel number 5.
kTPM_Chnl_6|TPM channel number 6.
kTPM_Chnl_7|TPM channel number 7.

<span id="enum3"></span>

	enum tpm_pwm_level_select_t

值|说明
-|-
kTPM_NoPwmSignal|No PWM output on pin.
kTPM_LowTrue|Low true pulses.
kTPM_HighTrue|High true pulses.	

<span id="enum4"></span>

	enum tpm_pwm_mode_t

值|说明
-|-
kTPM_EdgeAlignedPwm|Edge aligned PWM.
kTPM_CenterAlignedPwm|Center aligned PWM.

<span id="enum5"></span>

	enum tpm_clock_source_t

值|说明
-|-
kTPM_SystemClock|System clock.
kTPM_ExternalClock|External clock.


    
