/**
 * @file main.c
 * @brief Warbling Digital Wire - ECE 444 HW1
 * @author Cole Zenk
 *
 * Implements a digital passthrough with amplitude modulation (warble).
 * Samples ADC at 10kHz, applies envelope, outputs to DAC.
 */

#include "MK22F51212.h"
#include "ADC.h"
#include "DAC.h"
#include "MCG.h"
#include "TimerInt.h"

/* #include "WarblingWire.h" */
/* #include "wire_inverter.h" */
#include  "fourier_synth.h"

static void GPIO_Init(void){
    // Gate clocks for Ports A-D
    SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK
                 | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK;

    // Red LED - PTA1 as GPIO output
    PORTA->PCR[1] = PORT_PCR_MUX(1);
    GPIOA->PDDR |= (1<<1);   // Set as output

    // Buttons as GPIO input, (PE and PS) internal pullups, (IRQC(0xA) falling egde interupts.
    PORTC->PCR[1]  = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0xA);
    PORTB->PCR[17] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_IRQC(0xA);

    NVIC_ClearPendingIRQ(PORTC_IRQn);
    NVIC_EnableIRQ(PORTC_IRQn);
    NVIC_ClearPendingIRQ(PORTB_IRQn);
    NVIC_EnableIRQ(PORTB_IRQn);
}

int main(void) {

    // Other inits
    MCG_Clock120_Init();
    ADC_Init();
    ADC_Calibrate();
    DAC_Init();
    fourier_synth_init();
    TimerInt_Init();
    GPIO_Init();

    for(;;) {
        __WFI();  // Sleep until interrupt
    }
}
