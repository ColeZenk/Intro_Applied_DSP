/**
 * @file wire_inverter.h
 * @brief Spectral inverter system - SDR200 public interface
 * @author Cole Zenk
 *
 * Public interface for digital spectral inversion, frequency shifting,
 * and adjustable bit resolution systems.
 */
#include <stdint.h>
#ifndef SPECTRAL_MODULATION_H
#define SPECTRAL_MODULATION_H

#define PHASE_MODULATION_ACTIVE


#define BIT_RESOLUTION  (1u << 12u)          //4096
#define DC_OFFSET       (1u << 11u)          //2048
#define ADC_CHANNEL     12

#define EVEN            0

/* #define INVERT */
#define FREQ_SHIFT
/* #define TUNE_RESOLUTION */


#if defined(INVERT) && defined(TUNE_RESOLUTION) ||  \
    defined(FREQ_SHIFT) && defined(TUNE_RESOLUTION) || \
    defined(FREQ_SHIFT) && defined(INVERT)

    #error "Multiple spectral modulators enabled simultaneously"
#endif


/**
 * @brief Initialize the spectral inverter system
 *
 * Configures ADC, DAC, and timer interrupts for real-time signal processing.
 * If TUNE_RESOLUTION is defined, also initializes GPIO buttons for runtime
 * bit resolution adjustment.
 *
 * @note Must be called before enabling interrupts
 */
void spectral_inverter_init(void);

uint16_t apply_modulation(uint16_t input);

#ifdef TUNE_RESOLUTION
void init_buttons(void);
#endif

#endif /* SPECTRAL_MODULATION_H */
