# DAC
## 概述
MCUXpresso SDK为设备的数模转换模块提供外设驱动程序。
DAC驱动程序包括一个DAC转换器和一个DAC缓冲区。通过使用此数模转换，用户可以在相应的DAC电压输出pin检测到输出电压，本开发板为pin J10-11。

函数[`DAC_Init`](#func1)初始化DAC数模转换模块。
函数[`DAC_GetDefaultConfig`](#func2)将用户配置结构初始化为默认值。
函数[`DAC_Enable`](#func3)使能DAC模块，使其能够输出。
函数[`DAC_SetBufferReadPointer(DAC_Type *base, uint8_t index)`](#func4)设置目前的DAC缓冲区read指针确保DAC模块目前的读指针指向第一个要读取的数值。

##功能函数
### <span id="func1">DAC_Init</span>

    void DAC_Init(DAC_Type *base, const dac_config_t *config)
`base`：DAC外围设备的基地址。
 `*config`：配置结构的配置指针（#struct1）。
    config->dac_reference_voltage_source_t referenceVoltageSource = kDAC_ReferenceVoltageSourceVref2; 
    config->bool enableLowPowerMode = false;

### <span id="func2">DAC_GetDefaultConfig</span>

    void DAC_GetDefaultConfig(dac_config_t *config)
`*config`：配置结构的配置指针（#struct1）。

### <span id="func3">DAC_Enable</span>

    static inline void DAC_Enable(DAC_Type *base, bool enable)
`base`:DAC外围设备的基地址。
`enable`:使能或者不使能该功能，为布尔值。

### <span id="func4">DAC_SetBufferReadPointer</span>

    void DAC_SetBufferReadPointer(DAC_Type *base, uint8_t index)
`base`DAC外围设备的基地址。
`index`为read指针设置的数值。
