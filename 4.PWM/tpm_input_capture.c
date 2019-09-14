#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_TPM_BASEADDR TPM1

/* TPM channel used for input capture */
#define BOARD_TPM_INPUT_CAPTURE_CHANNEL kTPM_Chnl_0

/* Interrupt number and interrupt handler for the TPM instance used */
#define TPM_INTERRUPT_NUMBER TPM1_IRQn
#define TPM_INPUT_CAPTURE_HANDLER TPM1_IRQHandler

/* Interrupt to enable and flag to read; depends on the TPM channel used */
#define TPM_CHANNEL_INTERRUPT_ENABLE kTPM_Chnl0InterruptEnable
#define TPM_CHANNEL_FLAG kTPM_Chnl0Flag


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
volatile bool tpmIsrFlag = false;

/*******************************************************************************
 * Code
 ******************************************************************************/
void TPM_INPUT_CAPTURE_HANDLER(void)
{
    tpmIsrFlag = true;

    /* Clear interrupt flag.*/
    TPM_ClearStatusFlags(DEMO_TPM_BASEADDR, TPM_CHANNEL_FLAG);
}

/*!
 * @brief Main function
 */
int main(void)
{
    tpm_config_t tpmInfo;
    uint32_t captureVal = 0;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    /* Print a note to terminal */
    PRINTF("\r\nTPM input capture example\r\n");
    PRINTF("\r\nOnce the input signal is received the input capture value is printed\r\n");

    TPM_GetDefaultConfig(&tpmInfo);
    /* Initialize TPM module */
    TPM_Init(DEMO_TPM_BASEADDR, &tpmInfo);

    /* Setup input capture on a TPM channel */
    TPM_SetupInputCapture(DEMO_TPM_BASEADDR, BOARD_TPM_INPUT_CAPTURE_CHANNEL, kTPM_FallingEdge);

    /* Set the timer to be in free-running mode */
    DEMO_TPM_BASEADDR->MOD = 0xFFFF;

    /* Enable channel interrupt when the second edge is detected */
    TPM_EnableInterrupts(DEMO_TPM_BASEADDR, TPM_CHANNEL_INTERRUPT_ENABLE);

    /* Enable at the NVIC */
    EnableIRQ(TPM_INTERRUPT_NUMBER);

    TPM_StartTimer(DEMO_TPM_BASEADDR, kTPM_SystemClock);

    while (tpmIsrFlag != true)
    {
    }

    captureVal = DEMO_TPM_BASEADDR->CONTROLS[BOARD_TPM_INPUT_CAPTURE_CHANNEL].CnV;

    PRINTF("\r\nCapture value C(n)V=%x\r\n", captureVal);
    while (1)
    {
    }
}
