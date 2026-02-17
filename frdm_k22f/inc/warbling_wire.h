#ifndef WARBLINGWIRE_H
#define WARBLINGWIRE_H
#include <math.h>

/**************************************************************************
  TWEAKING VALUES
 **************************************************************************/

/**
 * @macros  Functional options
 * @purpose Through this macro you can define the ADC channel used.
 */

// Envelope range: 10% to 100% scale
#define GAIN_MIN                   0.1f
#define GAIN_MAX                   1.0f
#define GAIN_OFFSET                (GAIN_MAX + GAIN_MIN) / 2.0f    // 0.55 center
#define GAIN_AMPLITUDE             (GAIN_MAX - GAIN_MIN) / 2.0f    // +/- 0.45

#define F_PI                       (float)M_PI
#define SAMPLING_FREQ              10000.0f                        // Samples every 10 us
#define NORMALIZE_FREQ_CONST       2.0f * F_PI / SAMPLING_FREQ
#define FREQUENCY_WARBLE_HZ        3.0f * NORMALIZE_FREQ_CONST

#define BITS                       (12u)
#define BIT_RESOLUTION             (1u << BITS)                    // 2 raised to BITS
#define ADC_CHANNEL                12                              // ADC0_SE12 (defined as PTB2-12 in ref-man 10.3)
/**************************************************************************
  GLOBAL FUNCTIONS (interfaces)
 **************************************************************************/

void WarbleWire(void);

// The init function to boot.
void WarblingWire_Init(void);


/**************************************************************************
  TESTING
 **************************************************************************/

/**
 * @macros   Test Procedure
 * @purpose  Comment or uncomment to disable certain features for clean encapsulated tests that
 *           enforce minimal coupling.
 */
/* #define TEST_PASSTHROUGH */
/* #define TEST_OUTPUT */

// Output test constants

#ifdef TEST_OUTPUT

#define TEST_SIGNAL_FREQ_HZ     100.0f
#define TEST_PERIOD             30000
typedef enum {
    WAVEFORM_SINE,
    WAVEFORM_TRIANGLE,
    WAVEFORM_SQUARE,

    WAVEFORM_COUNT
} Waveform_t;

#endif

#if defined(TEST_PASSTHROUGH) || defined(TEST_OUTPUT)
    #define TEST_MODE
    #warning "Test mode enabled"
#endif

#if defined(TEST_PASSTHROUGH) && defined(TEST_OUTPUT)
#define TEST_MODE
    #error "Multiple test modes enabled simultaneously"
#endif

#endif //WARBLINGWIRE_H
