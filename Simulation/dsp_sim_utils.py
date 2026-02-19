'''
dsp_sim_utils.py
A simple file containing simple utils to make DSP easier
'''
import matplotlib.pyplot as plot
from scipy import signal
from scipy import integrate
import numpy as np


def plot_phase_mag(num, den, title=None, save_path=None, ylim_mag=None):
    """Plot Bode magnitude and phase response"""
    H = signal.TransferFunction(num, den)
    angular_freq, magnitude, phase = signal.bode(H)

    fig, (ax1, ax2) = plot.subplots(2, 1, figsize=(10, 8))

    # Magnitude
    ax1.semilogx(angular_freq, magnitude)
    ax1.set_ylabel('Magnitude (dB)')
    ax1.grid(True, which="both", ls="-", color='0.65')

    if ylim_mag:
        ax1.set_ylim(ylim_mag)

    # Phase
    ax2.semilogx(angular_freq, phase)
    ax2.set_xlabel('Frequency (rad/s)')
    ax2.set_ylabel('Phase (deg)')
    ax2.grid(True, which="both", ls="-", color='0.65')

    if title:
        ax1.set_title(title)  # Use ax1.set_title

    plot.tight_layout()

    if save_path:
        plot.savefig(save_path, dpi=300, facecolor='black')

    plot.show()


def plot_pole_zero(num, den, title=None, save_path=None):
    """Plot pole-zero diagram"""
    zeros, poles, gain = signal.tf2zpk(num, den)

    plot.figure(figsize=(8, 8))
    plot.plot(np.real(zeros), np.imag(zeros), 'go', markersize=10,   # Green O
              label='Zeros', markeredgecolor='white')

    plot.plot(np.real(poles), np.imag(poles), 'rx', markersize=10,   # Red X
              label='Poles', markeredgewidth=2)

    plot.axhline(0, color='white', linewidth=0.5)
    plot.axvline(0, color='white', linewidth=0.5)

    plot.grid(True, alpha=0.3)
    plot.xlabel('Real')
    plot.ylabel('Imaginary')
    plot.legend()

    plot.axis('equal')
    plot.xticks(np.arange(-3, 3, 0.5))
    plot.yticks(np.arange(-3, 3, 0.5))

    if title:
        plot.title(title)

    if save_path:
        plot.savefig(save_path, dpi=300, facecolor='black')

    plot.show()


def find_omega_0(num, den, cutoff_db=-1):
    """
    Find the cutoff frequency for a given dB level.

    Parameters:
    - num, den: transfer function coefficients
    - cutoff_db: cutoff level in dB (default: -1 dB)

    Returns:
    - omega_0: cutoff frequency in rad/s
    """
    omega = np.logspace(-2, 2, 10000)  # 10000 logs in 10^-2 : 10^2 rad/s
    omega_vals, h = signal.freqs(num, den, worN=omega)
    magnitude = np.abs(h)

    # Search all frequencies and find which one gives closest magnitude
    target_mag = 10**(cutoff_db/20)  # 10^(dB/20) = 10^(log10(mag)) = linmag
    index = np.argmin(np.abs(magnitude - target_mag))  # Find closest match
    omega_0 = omega_vals[index]

    return omega_0


def find_fft_k(T, function, K_max, C_1=0, C_2=1, C_3=1):
    Y_k = np.zeros(K_max+1, dtype=complex)
    omega_0 = 2 * np.pi / T

    def integrand_real(t, k):
        return function(t) * np.cos(k * omega_0 * t)

    def integrand_imag(t, k):
        return function(t) * np.sin(k * omega_0 * t)

    Y_k[0] = (C_2 / T) * integrate.quad(function, -T/2, T/2)[0] + C_1

    for k in range(1, K_max + 1):
        real_part = integrate.quad(integrand_real, -T/2, T/2, args=(k,), limit=200)[0]
        imag_part = integrate.quad(integrand_imag, -T/2, T/2, args=(k,), limit=200)[0]
        Y_k[k] = (C_2 / T) * (real_part - 1j * imag_part)

    return Y_k


def fft_synth_real(Y_k, omega_0, K, t):
    y = np.real(Y_k[0]) * np.ones(len(t))
    for k in range(1, K+1):
        a_k = 2 * np.real(Y_k[k])      # Factor of 2 to account for -k
        b_k = -2 * np.imag(Y_k[k])

        # Apply Eulers and seperate for hardware realization (C doesn't do j)
        y += a_k * np.cos(k * omega_0 * t) + b_k * np.sin(k * omega_0 * t)
    return y
