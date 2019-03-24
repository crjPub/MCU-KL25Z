# ADC
## 概述
MCUXpresso SDK为设备的16位SAR模数转换模块提供外设驱动程序。  

函数[`ADC16_Init`](#func1)初始化ADC16模块。  
函数[`ADC16_GetDefaultConfig`](#func2)获取转换器配置的可用预定义设置，即用默认的配置初始化。   
函数[`ADC16_DoAutoCalibration`](#func3)自动进行硬件校准。  
函数[`ADC16_SetOffsetValue`](#func4)设置转换结果的偏移值。  
函数[`ADC16_EnableHardwareTrigger`](#func5)启用硬件触发模式。  
函数[`ADC16_SetChannelConfig`](#func6)配置转换通道。  

## 功能函数
### <span id="func1">ADC16_Init</span>

	void ADC16_Init(ADC_Type* base, const adc16_config_t* config)
`base`：ADC16外设基址  
`config`：配置[`adc16_config_t`](#struct1)类型指针

	void ADC16_Deinit(ADC_Type* base)
`base`：ADC16外设基址  

### <span id="func2">ADC16_GetDefaultConfig</span>

	void ADC16_GetDefaultConfig(adc16_config_t* config)
`config`：配置[`adc16_config_t`](#struct1)类型指针

	config->referenceVoltageSource=kADC16_ReferenceVoltageSourceVref;
	config->clockSource =  kADC16_ClockSourceAsynchronousClock;
	config->enableAsynchronousClock = true;
	config->clockDivider = kADC16_ClockDivider8;
	config->resolution = kADC16_ResolutionSE12Bit;
	config->longSampleMode = kADC16_LongSampleDisabled;
	config->enableHighSpeed = false;
	config->enableLowPower = false;
	config->enableContinuousConversion = false;

### <span id="func3">ADC16_DoAutoCalibration</span>
此自动校准有助于自动调整正负侧增益。使用转换器前执行校准。请注意，校准期间应使用硬件触发器。  

	status_t ADC16_DoAutoCalibration(ADC_Type* base)	
`base`：ADC16外设基址   

### <span id="func4">ADC16_SetOffsetValue</span>
此偏移值对转换结果生效。如果偏移值不是零，则读数结果将被减去。注意，硬件校准会自动填充偏移值。  

	static void ADC16_SetOffsetValue(ADC_Type* base, int16_t value)
`base`：ADC16外设基址  
`value`：设置偏移值  

### <span id="func5">ADC16_EnableHardwareTrigger</span>

	static void ADC16_EnableHardwareTrigger(ADC_Type* base, bool enable)
`base`：ADC16外设基址   
`enable`：硬件触发功能的切换。`true`表示启用，`false`表示未启用   

### <span id="func6">ADC16_SetChannelConfig</span>

	void ADC16_SetChannelConfig(ADC_Type* base, uint32_t channelGroup, const adc16_channel_config_t* config)


## 数据结构
### <span id="struct1">`struct adc16_config_t`</span>

参数表

参数名|参数类型|说明
-|-|-
referenceVoltageSource|[`adc16_reference_voltage_source_t`](#enum1)|选择参考电压源
clockSource|[`adc16_clock_source_t`](#enum2)|选择转换器的输入时钟源
enableAsynchronousClock|bool|启用异步时钟输出
clockDivider|[`adc16_clock_divider_t`](#enum3)|选择输入时钟源的分频器
resolution|[`adc16_resolution_t`](#enum4)|选择采样分辨率模式
longSampleMode|[`adc16_long_sample_mode_t`](#enum5)|选择长采样模式
enableHighSpeed|bool|启用高速模式
enableLowPower|bool|启用低功率
enableContinuousConversion|bool|启用连续转换模式

### <span id="struct2">`struct adc16_channel_config_t`</span>

参数表

参数名|参数类型|说明
-|-|-
channelNumber|uint32_t|设置转换通道编号，可选范围为0~31，详见芯片参考手册。
enableInterruptOnConversionCompleted|bool|转换完成后产生中断
enableDifferentialConversion|bool|使用差分采样模式


## 枚举类型
### <span id="enum1">`enum adc16_reference_voltage_source_t`</span>

值|说明
-|-
kADC16_ReferenceVoltageSourceVref|For external pins pair of VrefH and VrefL.
kADC16_ReferenceVoltageSourceValt|For alternate reference pair of ValtH and ValtL.

### <span id="enum2">`enum adc16_clock_source_t`</span>

值|说明
-|-
kADC16_ClockSourceAlt0|Selection 0 of the clock source.
kADC16_ClockSourceAlt1|Selection 1 of the clock source.
kADC16_ClockSourceAlt2|Selection 2 of the clock source.
kADC16_ClockSourceAlt3|Selection 3 of the clock source.
kADC16_ClockSourceAsynchronousClock|Using internal asynchronous clock.

### <span id="enum3">`enum adc16_clock_divider_t`</span>

值|说明
-|-
kADC16_ClockDivider1|For divider 1 from the input clock to the module.
kADC16_ClockDivider2|For divider 2 from the input clock to the module.
kADC16_ClockDivider4|For divider 4 from the input clock to the module.
kADC16_ClockDivider8|For divider 8 from the input clock to the module.

### <span id="enum4">`enum adc16_resolution_t`</span>

值|说明
-|-
kADC16_Resolution8or9Bit|Single End 8-bit or Differential Sample 9-bit.
kADC16_Resolution12or13Bit|Single End 12-bit or Differential Sample 13-bit.
kADC16_Resolution10or11Bit|Single End 10-bit or Differential Sample 11-bit.
kADC16_ResolutionSE8Bit|Single End 8-bit.
kADC16_ResolutionSE12Bit|Single End 12-bit.
kADC16_ResolutionSE10Bit|Single End 10-bit.
kADC16_ResolutionDF9Bit|Differential Sample 9-bit.
kADC16_ResolutionDF13Bit|Differential Sample 13-bit.
kADC16_ResolutionDF11Bit|Differential Sample 11-bit.
kADC16_Resolution16Bit|Single End 16-bit or Differential Sample 16-bit.
kADC16_ResolutionSE16Bit|Single End 16-bit.
kADC16_ResolutionDF16Bit|Differential Sample 16-bit.

### <span id="enum5">`enum adc16_long_sample_mode_t`</span>

值|说明
-|-
kADC16_LongSampleCycle24|20 extra ADCK cycles, 24 ADCK cycles total.
kADC16_LongSampleCycle16|12 extra ADCK cycles, 16 ADCK cycles total.
kADC16_LongSampleCycle10|6 extra ADCK cycles, 10 ADCK cycles total.
kADC16_LongSampleCycle6|2 extra ADCK cycles, 6 ADCK cycles total.
kADC16_LongSampleDisabled|Disable the long sample feature.


	enum adc16_clock_source_t

值|说明
-|-
kADC16_ClockSourceAlt0|Selection 0 of the clock source.
kADC16_ClockSourceAlt1|Selection 1 of the clock source.
kADC16_ClockSourceAlt2|Selection 2 of the clock source.
kADC16_ClockSourceAlt3|Selection 3 of the clock source.
kADC16_ClockSourceAsynchronousClock|Using internal asynchronous clock.

# DAC
## 概述
MCUXpresso SDK为设备的数模转换模块提供外设驱动程序。DAC驱动程序包括一个基本的DAC模块（转换器）和一个DAC缓冲区。基本的DAC模块支持每个DAC实例中DAC转换器特有的操作。  
