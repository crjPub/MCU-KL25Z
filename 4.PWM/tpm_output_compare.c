#include "fsl_debug_console.h"
#include "board.h"
#include "fsl_tpm.h"

#include "pin_mux.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define DEMO_TPM_BASEADDR TPM2
#define BOARD_TPM_OUT_CHANNEL kTPM_Chnl_1


/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Main function
 */
int main(void)
{
    tpm_config_t tpmInfo;
    uint32_t compareValue = 0x1000;

    /* Board pin, clock, debug console init */
    BOARD_InitPins();
    BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    /* Select the clock source for the TPM counter as kCLOCK_PllFllSelClk */
    CLOCK_SetTpmClock(1U);

    /* Print a note to terminal */
    PRINTF("\r\nTPM example for output compare\r\n");
    PRINTF("\r\nYou will see the output signal toggle");
    PRINTF("\r\nProbe the signal using an oscilloscope");

    TPM_GetDefaultConfig(&tpmInfo);
    /* Initialize TPM module */
    TPM_Init(DEMO_TPM_BASEADDR, &tpmInfo);

    /* Setup the output compare mode to toggle output on a match */
    TPM_SetupOutputCompare(DEMO_TPM_BASEADDR, BOARD_TPM_OUT_CHANNEL, kTPM_ToggleOnMatch, compareValue);

    /* Set the timer to be in free-running mode */
    DEMO_TPM_BASEADDR->MOD = 0xFFFF;

    TPM_StartTimer(DEMO_TPM_BASEADDR, kTPM_SystemClock);
    while (1)
    {
    }
}
