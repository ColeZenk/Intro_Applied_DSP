/**
 * @file fourier_synth.h
 * @brief Fourier Series Synthesizer - SDD301 & SDD302
 * @author Cole Zenk
 *
 * Public interface for truncated Fourier series synthesis.
 * Outputs y_K(t) on DAC at 10 kHz sample rate.
 * K adjustable 1-10 via button presses at runtime.
 */

#ifndef FOURIER_SYNTH_H
#define FOURIER_SYNTH_H

#include <stdint.h>

/*************************************************************************
 CONSTANTS
 *************************************************************************/
#define FOURIER_SYNTH_ACTIVE
#define FS              10000.0f                  // Sample rate (Hz)

#define KMAX            10u
#define T               40.0f                     // Base unit signal period
#define PERIOD_SAMPLES  22u                       // 23 samples per period (SDD302)
                                                  // Note: Decreasing below 23 samples may
                                                  //       raise the risk of aliasing because
                                                  //       Refer to SDD301 section :

#define F0              (FS / (float)PERIOD_SAMPLES)
#define OMEGA_0         (2.0f * 3.14159265f * F0)

#define C1              410.0f              // DAC DC offset
#define C2              1843.0f             // Amplitude scaling
#define C3              F0 * T              // Time scaling

/*************************************************************************
 PUBLIC INTERFACE
 *************************************************************************/

/**
 * @brief Precompute and populate LUT for all K values at startup.
 *        Call once before enabling interrupts.
 */
void fourier_synth_init(void);
uint16_t fourier_synth_debug(void);
/**
 * @brief Get next DAC sample. Call from ISR.
 * @return 12-bit DAC value (0-4095)
 */
uint16_t fourier_synth_sample(void);

/**
 * @brief Increment K (max 10). Call on button press.
 */
void fourier_synth_k_inc(void);

/**
 * @brief Decrement K (min 1). Call on button press.
 */
void fourier_synth_k_dec(void);
#endif /* FOURIER_SYNTH_H */
