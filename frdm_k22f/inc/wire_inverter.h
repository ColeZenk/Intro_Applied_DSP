/**
 * @file wire_inverter.h
 * @brief Spectral inverter system - SDR200 public interface
 * @author Cole Zenk
 *
 * Public interface for digital spectral inversion, frequency shifting,
 * and adjustable bit resolution systems.
 */

#ifndef WIRE_INVERTER_H
#define WIRE_INVERTER_H


#define BIT_RESOLUTION  (1u << 12u)          //4096
#define DC_OFFSET       (1u << 11u)          //2048
#define ADC_CHANNEL     12

#define EVEN            0

/* #define INVERT */
/* #define FREQ_SHIFT */
#define TUNE_RESOLUTION

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

#ifdef TUNE_RESOLUTION
void init_buttons(void);
#endif

#endif /* WIRE_INVERTER_H */
