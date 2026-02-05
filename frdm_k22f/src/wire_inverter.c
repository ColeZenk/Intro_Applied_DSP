/**
 * @file wire_inverter.c
 * @brief Spectral inverter system - SDR200
 * @author Cole Zenk
 *
 * Implements a digital spectral inversion system.
 *
 * @scope
 * File coverers encapsulated implementation of the "algorithm" as well as some minimal
 *      unit testing and verification methods.
 */

/*************************************************************************
 INCLUDES
 *************************************************************************/
#include <stdbool.h>
#include <stdint.h>

#include "MK22F51212.h"
#include "TimerInt.h"
#include "wire_inverter.h"

/*************************************************************************
 File scope
 *************************************************************************/
static inline uint16_t process_input(uint16_t input);

/*************************************************************************
 Primary logic implementations
 ************************************************************************/

#ifdef INVERT
__attribute__((always_inline))
static inline uint16_t spectral_invert(uint16_t input)
{
    static bool spectral_state = EVEN;
    spectral_state ^= 1;
    return spectral_state ? (4096u - input) : input;
}
#endif

#ifdef FREQ_SHIFT
__attribute__((always_inline))
static inline uint16_t frequency_shift(uint16_t input)
{
    static uint8_t state = 0;
    static const int8_t states[4] = {0, 1, 0, -1};   // mini LUT

    int16_t normalized_input = (int16_t)input - DC_OFFSET;
    uint16_t output = DC_OFFSET + normalized_input * states[state];

    state = (state + 1) & 0x03;

    return output;
}
#endif

#ifdef TUNE_RESOLUTION
__attribute__((always_inline))
static inline uint16_t manual_tune(uint16_t input)
{
    static uint8_t current_resolution = 4;

    uint16_t mask = 0xFFFF << (12 - current_resolution);
    return input & mask;
}
#endif

/*************************************************************************
 Global init and ISR
 *************************************************************************/

__attribute__((hot))
void PIT0_IRQHandler(void)
{
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;

    uint16_t adc_sample = ADC0->R[0];              // Read previous result
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);      // Start next conversion

    uint16_t output = process_input(adc_sample);
    // Write to DAC (12-bit)
    DAC0->DAT[0].DATL = output & 0xFF;
    DAC0->DAT[0].DATH = (output >> 8) & 0x0F;
}

void spectral_inverter_init(void)
{
    TimerInt_Init();
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);
}


#ifdef TUNE_RESOLUTION
void init_buttons(void)
{
    // Enable PORTC clock
    SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTB_MASK;

    //  Configure SW2 on PTC1 (GPIO input with internal pullup)
    PORTC->PCR[1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    GPIOC->PDDR &= ~(1<<1); // Set as input


    //  Configure SW3 on PTB17 (GPIO input with internal pullup)
    PORTB->PCR[17] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
    GPIOB->PDDR &= ~(1<<17);  // Set as inputs
}
#endif

/*************************************************************************
 File scoped implementations
 *************************************************************************/
__attribute__((always_inline))
static inline uint16_t process_input(uint16_t input)
{
#ifdef INVERT
    return spectral_invert(input);
#elif defined(FREQ_SHIFT)
    return frequency_shift(input);
#elif defined(TUNE_RESOLUTION)
    return manual_tune(input);
#endif
}

