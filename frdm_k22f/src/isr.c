/**
 * @file isr.c
 * @brief A container for all interupt service routines
 * @author Cole Zenk
 */

#include "MK22F51212.h"

#include "TimerInt.h"
#include "spectral_modulation.h"
#include "warbling_wire.h"

void PIT0_IRQHandler(void)
{
    static uint16_t processed_input = 0;

    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    uint16_t adc_sample = ADC0->R[0];              // Read previous result
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);      // Start next conversion

#if defined(SPECTRAL_MODULATION_ACTIVE)
     processed_input = apply_spectral_mod(adc_sample);
#elif defined(AMPLITUDE_MODULATION_ACTIVE)

#else //passthrough
    processed_input = adc_sample;
#endif


    uint16_t output = processed_input;
    // Write to DAC (12-bit)
    DAC0->DAT[0].DATL = output & 0xFF;
    DAC0->DAT[0].DATH = (output >> 8) & 0x0F;
}
