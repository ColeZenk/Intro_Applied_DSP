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

#include "Utilities.h"
#include "MK22F51212.h"
#include "TimerInt.h"
#include "spectral_modulation.h"

/*************************************************************************
 File scope
 *************************************************************************/
static bool nyquist_clock = 0x0;

/*************************************************************************
 Primary logic implementations
 ************************************************************************/

#ifdef INVERT
__attribute__((always_inline))
static inline uint16_t spectral_invert(uint16_t input, bool clock)
{
    /* static bool spectral_state = EVEN; */
    /* spectral_state ^= 1; */
    /* return spectral_state ? (4096u - input) : input; */

    int16_t signed_input = (int16_t)input - DC_OFFSET;
    signed_input = COND_NEGATE(signed_input, clock);
    return (uint16_t)(signed_input + DC_OFFSET);
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
void spectral_inverter_init(void)
{
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);
}

uint16_t apply_modulation(uint16_t input)
{
#ifdef INVERT
    return spectral_invert(input, nyquist_clock);
#elif defined(FREQ_SHIFT)
    return frequency_shift(input);
#elif defined(TUNE_RESOLUTION)
    return manual_tune(input);
#endif
    nyquist_clock ^= 1;
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

