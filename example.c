#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_pit.h"
#include "fsl_tpm.h"

/*******************************************************************************
 * 宏定义
 ******************************************************************************/
#define RED_LED_GPIO BOARD_LED_RED_GPIO
#define RED_LED_GPIO_PIN BOARD_LED_RED_GPIO_PIN
#define GREEN_LED_GPIO BOARD_LED_GREEN_GPIO
#define GREEN_LED_GPIO_PIN BOARD_LED_GREEN_GPIO_PIN
#define BLUE_LED_GPIO BOARD_LED_BLUE_GPIO
#define BLUE_LED_GPIO_PIN BOARD_LED_BLUE_GPIO_PIN
#define PIT_IRQ_ID PIT_IRQn  // PIT中断号
/* Get source clock for PIT driver */
#define PIT_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_BusClk)  // 时钟为总线时钟

//TPM
#define BOARD_TPM_BASEADDR TPM2
#define BOARD_TPM_CHANNEL 0U

/* 中断以启用和标记读取；取决于使用的TPM通道  */
#define TPM_CHANNEL_INTERRUPT_ENABLE kTPM_Chnl1InterruptEnable
#define TPM_CHANNEL_FLAG kTPM_Chnl1Flag

/* 所用TPM实例的中断号和中断处理程序 */
#define TPM_INTERRUPT_NUMBER TPM2_IRQn
#define TPM_LED_HANDLER TPM2_IRQHandler

/* 得到TPM模块的时钟源：PLLFLLSELCLK */
#define TPM_SOURCE_CLOCK CLOCK_GetFreq(kCLOCK_PllFllSelClk)


/*******************************************************************************
 * Prototypes
 ******************************************************************************/
// 延时函数
void delay(void);

/*******************************************************************************
 *变量
 ******************************************************************************/
unsigned int red_state=0;
unsigned int green_state=0;
unsigned int blue_state=0;
unsigned int period = 100;
volatile bool pitIsrFlag = false;  // 用于标记计数是否达到周期值；
int up = 1;

volatile bool brightnessUp = true; // 指示LED灯变亮或变暗
volatile uint8_t updatedDutycycle = 10U;
volatile uint8_t getCharValue = 0U;

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 8000000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

int main(void)
{
    /* 定义输出LED管脚的初始化结构 */
    // kGPIO_DigitalOutput定义为输出，0：输出低电平；
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    /* 初始PIT的结构体 */
    pit_config_t pitConfig;

    /* 板针，时钟，调试控制台初始化 */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    // pitConfig.enableRunInDebug = false;
    // 计数器在debug模式下被禁止；
    PIT_GetDefaultConfig(&pitConfig);

    /* 初始化PIT模块 */
    PIT_Init(PIT, &pitConfig);

    /* 设置通道0的计数周期 */
    // 周期值为 1000 000 * 24 000 000 / 1000 000 =24 000 000
    // 若改变计数值周期，可直接改USEC_TO_COUNT(us U, PIT_SOURCE_CLOCK)中的us即可；
    PIT_SetTimerPeriod(PIT, kPIT_Chnl_0, USEC_TO_COUNT(period*1000U, PIT_SOURCE_CLOCK));

    /* 使能通道0的计数器中断  */
    PIT_EnableInterrupts(PIT, kPIT_Chnl_0, kPIT_TimerInterruptEnable);

    /* 在内嵌向量中断控制器中使能 */
    EnableIRQ(PIT_IRQ_ID);

    /* 启动计数器0 */
    PRINTF("\r\nStarting channel No.0 ...");
    PIT_StartTimer(PIT, kPIT_Chnl_0);

    /* 初始化LED输出 */
    /*
    GPIO_PinInit(RED_LED_GPIO, RED_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(GREEN_LED_GPIO, GREEN_LED_GPIO_PIN, &led_config);
    GPIO_PinInit(BLUE_LED_GPIO, BLUE_LED_GPIO_PIN, &led_config);
    GPIO_ClearPinsOutput(RED_LED_GPIO, 1u << RED_LED_GPIO_PIN);
    GPIO_ClearPinsOutput(GREEN_LED_GPIO, 1u << GREEN_LED_GPIO_PIN);
    GPIO_ClearPinsOutput(BLUE_LED_GPIO, 1u << BLUE_LED_GPIO_PIN);
    */

    tpm_config_t tpmInfo;
    /*
     * TPM通道的配置；
     * 脉宽调制输出有源电平选择；
     * 脉宽调制脉冲宽度，值应在0到100之间，即占空比；
     * 第一个脉宽的配置；
     */
    tpm_chnl_pwm_signal_param_t tpmParam;   // 配置TPM通道的PWM信号的选项；
    //TPM PWM输出脉冲模式：高、低或无输出
    tpm_pwm_level_select_t pwmLevel = kTPM_LowTrue; // 配置为低输出模式；

    /* 配置频率为24kHz的TPM */
    tpmParam.chnlNumber = (tpm_chnl_t)BOARD_TPM_CHANNEL; // 通道配置；配置为通道1；
    tpmParam.level = pwmLevel;  // 低输出模式；
    tpmParam.dutyCyclePercent = updatedDutycycle; // 占空比配置；


    /* 选择TPM模块的时钟源为PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    /* Print a note to terminal */
    PRINTF("\r\nTPM example to output center-aligned PWM signal\r\n");
    PRINTF("\r\nIf an LED is connected to the TPM pin, you will see a change in LED brightness if you enter different values");
    PRINTF("\r\nIf no LED is connected to the TPM pin, then probe the signal using an oscilloscope");

    TPM_GetDefaultConfig(&tpmInfo);
    /* 初始化TPM模块 */
    TPM_Init(BOARD_TPM_BASEADDR, &tpmInfo);

    /*
     * 配置PWM模块的参数；
     * BOARD_TPM_BASEADDR：TPM模块的基地址；
     * tpmParam：通道参数的配置；
     * 1U：通道号；
     * kTPM_CenterAlignedPwm：脉宽调制的操作模式，应为枚举类型中的值，此处配置为中心对称脉宽；
     * 24000：PWM信号的频率；
     * TPM_SOURCE_CLOCK：时钟源；
     */
    TPM_SetupPwm(BOARD_TPM_BASEADDR, &tpmParam, 1U, kTPM_CenterAlignedPwm, 1000U, TPM_SOURCE_CLOCK);
    /* 启动计数器  */
    TPM_StartTimer(BOARD_TPM_BASEADDR, kTPM_SystemClock);

    while (1)
    {

        if (true == pitIsrFlag)
        {
            pitIsrFlag = false;
            if (up ==1)
                getCharValue = getCharValue + 3;
            else
                getCharValue = getCharValue - 3;
            if (getCharValue >= 99)
                up = 0;
            if (getCharValue <= 1)
                up = 1;

                updatedDutycycle = getCharValue;

                /* 更新占空比之前禁用通道输出  */
                TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, 0U); //更新通道的边缘级别选择

                /* 更新PWM占空比 */
                TPM_UpdatePwmDutycycle(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, kTPM_CenterAlignedPwm,
                                       updatedDutycycle);

                /* 开启通道输出，输出新的占空比 */
                TPM_UpdateChnlEdgeLevelSelect(BOARD_TPM_BASEADDR, (tpm_chnl_t)BOARD_TPM_CHANNEL, pwmLevel);

                PRINTF("The duty cycle was successfully updated!\r\n");
        }


    }
}

void PIT_IRQHandler(void)
{
    // 清除中断标志；
    PIT_ClearStatusFlags(PIT, kPIT_Chnl_0, kPIT_TimerFlag);
    pitIsrFlag = true;
}


