/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"

#include "clock_config.h"
#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define RED_GPIO BOARD_LED_RED_GPIO
#define GREEN_GPIO BOARD_LED_GREEN_GPIO
#define BLUE_GPIO BOARD_LED_BLUE_GPIO
#define RED_GPIO_PIN BOARD_LED_RED_GPIO_PIN
#define GREEN_GPIO_PIN BOARD_LED_GREEN_GPIO_PIN
#define BLUE_GPIO_PIN BOARD_LED_BLUE_GPIO_PIN

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief delay a while.
 */
void delay(void);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
void delay(void)
{
    volatile uint32_t i = 0;
    for (i = 0; i < 800000; ++i)
    {
        __asm("NOP"); /* delay */
    }
}

/*!
 * @brief Main function
 */
int main(void)
{
    /* Define the init structure for the output LED pin*/
    gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput, 0,
    };

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    //BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Print a note to terminal. */
    PRINTF("\r\n GPIO Driver example\r\n");
    PRINTF("\r\n The LED is taking turns to shine.\r\n");

    /* Init output LED GPIO. */
    GPIO_PinInit(RED_GPIO, RED_GPIO_PIN, &led_config);
    GPIO_PinInit(GREEN_GPIO, GREEN_GPIO_PIN, &led_config);
    GPIO_PinInit(BLUE_GPIO, BLUE_GPIO_PIN, &led_config);
    GPIO_ClearPinsOutput(BLUE_GPIO, 1u << BLUE_GPIO_PIN);
    GPIO_ClearPinsOutput(RED_GPIO, 1u << RED_GPIO_PIN);
    GPIO_ClearPinsOutput(GREEN_GPIO, 1u << GREEN_GPIO_PIN);
    //int flag=0;

    while (1)
    {/*
    	switch(flag){
    	case 0: GPIO_ClearPinsOutput(BLUE_GPIO, 1u << BLUE_GPIO_PIN); GPIO_SetPinsOutput(RED_GPIO, 1u << RED_GPIO_PIN); break;
    	case 1: GPIO_ClearPinsOutput(RED_GPIO, 1u << RED_GPIO_PIN); GPIO_SetPinsOutput(GREEN_GPIO, 1u << GREEN_GPIO_PIN); break;
    	case 2: GPIO_ClearPinsOutput(GREEN_GPIO, 1u << GREEN_GPIO_PIN); GPIO_SetPinsOutput(BLUE_GPIO, 1u << BLUE_GPIO_PIN);break;
    	}
    	flag=(flag+1)%3;*/
    	GPIO_TogglePinsOutput(GREEN_GPIO, 1u << GREEN_GPIO_PIN);
        delay();

    }
}
