/**
 * @file fourier_synth.c
 * @brief Fourier Series Synthesizer - ECE 444 HW3
 * @author Cole Zenk
 *
 * Implements truncated Fourier series synthesis via precomputed LUT.
 * Coefficients derived from numerical integration of x(t) in Python.
 * See SDD301.md for full derivation.
 *
 * y_K(t) = a0 + sum_{k=1}^{K} [ 2*Re(Yk)*cos(k*w0*t) - 2*Im(Yk)*sin(k*w0*t) ]
 */

/*************************************************************************
 INCLUDES
 *************************************************************************/
#include <math.h>
#include <stdint.h>

#include "fourier_synth.h"

/*************************************************************************
 COEFFICIENTS
 * a_k = Re{Y_k}, b_k = Im{Y_k}
 * Computed via find_fft_k(T=40, x, K=10, C1=410, C2=1843)
 * See SDD301.md for derivation
 *************************************************************************/
static const float a_k[KMAX + 1] = {
    1216.31250f,     // k=0  DC
     239.289971f,    // k=1
    -431.916129f,    // k=2
    -210.324415f,    // k=3
     140.142399f,    // k=4
       8.48982269f,  // k=5
    -109.377703f,    // k=6
      -0.805273241f, // k=7
      40.4644281f,   // k=8
     -13.1241907f,   // k=9
     -34.1638594f    // k=10
};

static const float b_k[KMAX + 1] = {
      0.0f,           // k=0  DC (no imaginary component)
    -165.95771119f,   // k=1
    -195.58403878f,   // k=2
      23.32248174f,   // k=3
     137.37739398f,   // k=4
     -55.14791232f,   // k=5
     -97.56772502f,   // k=6
      87.26825469f,   // k=7
      45.95872345f,   // k=8
     -94.88022582f,   // k=9
       4.83160338f    // k=10
};

/*************************************************************************
 FILE SCOPE
 *************************************************************************/
static uint16_t lut[KMAX][PERIOD_SAMPLES];
static uint8_t  K_current = 10;
static uint16_t sample_idx = 0;

/*************************************************************************
 INIT
 *************************************************************************/
void fourier_synth_init(void)
{
    for (int K = 0; K <= KMAX; K++) {
        for (int n = 0; n < PERIOD_SAMPLES; n++) {
            float t = (float)n / FS;
            float y = a_k[0];

            for (int k = 1; k <= K; k++) {   // K+1 harmonics for row K
                y += 2.0f * a_k[k] * cosf(k * OMEGA_0 * t)
                   - 2.0f * b_k[k] * sinf(k * OMEGA_0 * t);
            }

            if (y < 0.0f)    y = 0.0f;
            if (y > 4095.0f) y = 4095.0f;

            lut[K][n] = (uint16_t)y;
        }
    }
}

uint16_t fourier_synth_debug(void) {
    return lut[9][0];
}
/*************************************************************************
 ISR INTERFACE
 *************************************************************************/
uint16_t fourier_synth_sample(void)
{
    uint16_t sample = lut[K_current][sample_idx++];

    if (sample_idx >= PERIOD_SAMPLES)
        sample_idx = 0;

    return sample;
}

/*************************************************************************
 BUTTON HANDLERS
 *************************************************************************/
void fourier_synth_k_inc(void)
{
    if (K_current < KMAX) {
        K_current++;
        sample_idx = 0;     // Reset phase on K change
    }
}

void fourier_synth_k_dec(void)
{
    if (K_current > 1) {
        K_current--;
        sample_idx = 0;
    }
}
