#include <stdint.h>
#include <stdbool.h>
// includes da biblioteca driverlib
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#define CLOCK24 24000000
#define CLOCK120 120000000

uint8_t LED_D1 = 0;
int count = 0;

void main(void)
{
    uint32_t clock = SysCtlClockFreqSet(SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_480 | SYSCTL_XTAL_25MHZ, CLOCK24);

    bool toggle = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Habilita GPIO F (LED D4 = PF0)
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
        ; // Aguarda final da habilita��o

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_0); // LED D4 como sa�da
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, 0);       // LED D4 apagados
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_12MA, GPIO_PIN_TYPE_STD);

    while (1)
    {
        SysCtlDelay(8000000); // executa 3 instruções assembly
        // 24Mhz:
        // 1/24MHz = 41,67nS -> 41,67*3instr = 125,01 nS/exec
        // 125,01 nS * 8M = 1 s

        // 120Mhz:
        // 1/120MHz = 8,33nS -> 8,33*3instr = 25 nS/exec
        // 25 nS * 8M = 0.2 s

        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_0, toggle);
        toggle = toggle ? 0 : 1;
    }
}