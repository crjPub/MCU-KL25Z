# DAC
## 概述
MCUXpresso SDK为设备的数模转换模块提供外设驱动程序。
DAC驱动程序包括一个DAC转换器和一个DAC缓冲区。通过使用此数模转换，用户可以在相应的DAC电压输出pin检测到输出电压，本开发板为pin J10-11。

函数[`DAC_GetDefaultConfig`]将用户配置结构初始化为默认值。



函数[`ADC16_Init`](#func1)初始化ADC16模块。  
函数[`ADC16_GetDefaultConfig`](#func2)获取转换器配置的可用预定义设置，即用默认的配置初始化。   
函数[`ADC16_DoAutoCalibration`](#func3)自动进行硬件校准。  
函数[`ADC16_SetOffsetValue`](#func4)设置转换结果的偏移值。  
函数[`ADC16_EnableHardwareTrigger`](#func5)启用硬件触发模式。  
函数[`ADC16_SetChannelConfig`](#func6)配置转换通道。 
