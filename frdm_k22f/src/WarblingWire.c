/**
 * @file WarblingWire.c
 * @brief Warbling Digital Wire - ECE 444 HW1
 * @author Cole Zenk
 *
 * Implements a digital passthrough with amplitude modulation (warble).
 * Samples ADC at 10kHz, applies envelope, outputs to DAC.
 *
 * @scope
 * File coverers encapsulated implementation of the "algorithm" as well as some minimal
 *      unit testing and verification methods.
 */

/*************************************************************************
 INCLUDES
 *************************************************************************/
#include <math.h>
#include <stdbool.h>

#include "MK22F51212.h"
#include "TimerInt.h"


#include "WarblingWire.h"

#ifdef TEST_OUTPUT
#include "Utilities.h"

// Some floating point arithmatic
#define  VREFH                (3.0f)
#define  ADC_SCALE            (BIT_RESOLUTION / VREFH)

WaveGen_t test_osc;

static inline uint16_t outputTest(void);
#endif

/*************************************************************************
 FILE SCOPED FUNCTIONS
 *************************************************************************/
static inline uint16_t warbleTransform(uint16_t input);
static inline uint16_t processInput(uint16_t adc_sample);

#if defined(SPECTRAL_INVERTER)
static inline uint16_t spectral_invert(uint16_t input);
#endif

/*************************************************************************
 CORE ALGORITHM
 *************************************************************************/

__attribute__((always_inline))
static inline uint16_t warbleTransform(uint16_t input){
    static float accumulated_phase = 0.0f;

    // Calculations
    accumulated_phase += FREQUENCY_WARBLE_HZ;
    if( accumulated_phase >= 2.0f * F_PI ) accumulated_phase -= 2.0f * F_PI;

    float envelope = GAIN_OFFSET + GAIN_AMPLITUDE * sinf(accumulated_phase);   //0.1 to 1.0


    return (uint16_t)(input * envelope);
}

/*************************************************************************
 GLOBAL INTERFACE
 ************************************************************************/

/**
 * @function WarblingWire
 *
 * @purpose  A simple interfacing function allowing the warbling wire
 *           algorithm to be enabled. This architecture will reduce
 *           coupling, increase readability, while maintaining proper
 *           coheision.
 *
 * @brief    ADC Pipline: Reading result N-1 (previos read, old news)
 *           whilst starting conversion N. Init primes with first
 *           conversion, so the first ISR read is valid, then writes the
 *           output to a 12 bit DAC (depending on how ADC_CHANNEL is
 *           defind in WarblingWire.h)
 */

__attribute__((hot))
void WarbleWire(void){
    uint16_t adc_sample = ADC0->R[0];              // Read previous result
    ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);      // Start next conversion

    uint16_t output = processInput(adc_sample);

    // Write to DAC (12-bit)
    DAC0->DAT[0].DATL = output & 0xFF;
    DAC0->DAT[0].DATH = (output >> 8) & 0x0F;
}

__attribute__((hot))
void PIT0_IRQHandler(void) {
    PIT->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
    WarbleWire();
}

void WarblingWire_Init(void){
   TimerInt_Init();
   ADC0->SC1[0] = ADC_SC1_ADCH(ADC_CHANNEL);  // Prime the ISR
}

/*************************************************************************
 FILE SCOPED IMPLEMENTATIONS
 *************************************************************************/

__attribute__((always_inline))
static inline uint16_t processInput(uint16_t adc_sample){

#if !defined(TEST_MODE) || !defined(SPECTRAL_INVETER)

    return warbleTransform(adc_sample);

#elif  defined(TEST_PASSTHROUGH)
    return adc_sample;
#elif  defined(TEST_OUTPUT)
    adc_sample = outputTest();
    return adc_sample;
#elif defined(SPECTRAL_INVERTER)
    return spectral_invert(adc_sample);
#endif
}

#if defined(SPECTRAL_INVERTER)
__attribute__((always_inline))
static inline uint16_t spectral_invert(uint16_t input)
{
    static bool spectral_state = 1;
    spectral_state = !spectral_state;
    return spectral_state ? input : BIT_RESOLUTION - input;
}
#endif

/*************************************************************************
 TESTING
 *************************************************************************/
#ifdef TEST_OUTPUT

static inline uint16_t outputTest(void){
    static uint16_t testOutput = 0;
    static uint16_t   count = 0;
    static Waveform_t waveformToTest = 0;

    static bool first = true;
    if(first){
        WaveGen_Init(&test_osc, TEST_SIGNAL_FREQ_HZ, 1.5f * ADC_SCALE, 1.5f * ADC_SCALE);
        first = false;
    }

    switch(waveformToTest){
        case WAVEFORM_SINE:
             testOutput = warbleTransform((uint16_t)WaveGen_Sine(&test_osc));
             break;
        case WAVEFORM_TRIANGLE:
             testOutput = warbleTransform((uint16_t)WaveGen_Triangle(&test_osc));
             break;
        case WAVEFORM_SQUARE:
             testOutput = warbleTransform((uint16_t)WaveGen_Square(&test_osc));
             break;
        default:
             waveformToTest = WAVEFORM_SINE;
             testOutput = warbleTransform((uint16_t)WaveGen_Sine(&test_osc));
             break;
    }

    if(count >= TEST_PERIOD){
        waveformToTest++;
        count = 0;
    } else count++;

    return testOutput;
}
#endif

