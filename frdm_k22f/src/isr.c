/**
 * @file isr.c
 * @brief A container for all interupt service routines
 * @author Cole Zenk
 */

#include "MK22F51212.h"

#include "TimerInt.h"
/* #include "spectral_modulation.h" */
/* #include "warbling_wire.h" */
#include "fourier_synth.h"

void PIT0_IRQHandler(void){

    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

#if !defined(FOURIER_SYNTH_ACTIVE)
    static uint16_t processed_input = 0;
    uint16_t adc_sample = ADC0->R[0];              // Read previous result
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);      // Start next conversion

  #if defined(SPECTRAL_MODULATION_ACTIVE)
     processed_input = apply_spectral_mod(adc_sample);
  #elif defined(AMPLITUDE_MODULATION_ACTIVE)

  #else //passthrough
    processed_input = adc_sample;
  #endif
    uint16_t output = processed_input;

#else
    uint16_t output = fourier_synth_sample();
#endif

    // Write to DAC (12-bit)
    DAC0->DAT[0].DATL = output & 0xFF;
    DAC0->DAT[0].DATH = (output >> 8) & 0x0F;
}
