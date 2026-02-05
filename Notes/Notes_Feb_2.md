# February 2

## Example
"I want a low pass filter with a cut-off frequency of 3 kHz"

1. Keep it simple
$$
      \documentclass{article}
      \usepackage{circuitikz}
      \begin{document}

      \begin{circuitikz} \draw (0,0) to[V, v=$Vᵢₙ$] (0,4)
      to[R, l=$10Ω$] (2,4)
      to[C, l=$0.01F$, v=$V₂$] (4,2
      \end{circuitikz}

      \end{document}
$$

$$
\frac{x-y}{R} = c \derivative{y}
\derivative{y} + \frac{1}{RC} \times y = \frac{1}{RC} \times x
sY + \frac{1}{RC} \times Y = \frac{1}{RC} \times X

H(s) = \frac{Y(s)}{X(s)} = \frac{\frac{1}{RC}}{j\omega + \frac{1}{RC}} =  \frac{1}{j\omega RC + 1}
$$

### LPF
I want to set "parameter" so 30B is at 3kHz.

$$
h(t) = \frac{1}{RC} e^{-\frac{1}{RC}t}
f_{c} = 3000
\omega_{c} = 2\pi 3000
|H(j\omega_{c})| = 2^{-\frac{1}{2}} = (1 + (\omega_{c} RC)^{2})^{-\frac{1}{2}}
1 = \omega_{c}^{2} (RC)^{2}
RC = \frac{1}{\omega_{c}}
$$

What we can do,

$$
Let C = 1nF
2^{-\frac{1}{2}} = ((1 + (\omega_{c} RC)^{2})^{-\frac{1}{2}})^{10}
R = 14212.8\cdots
$$

NOTE: 3 db point is half power point (20log|10|)

## A More Traditional Approach | Butterworth Filter

$$
|H(j\omega)|^{2} = H(j\omega)H*(j\omega)
= H(j\omega)H(-j\omega)
= H(s)H(-s)
$$

H(s) is the filter we want, H(-s) is the evil twin (unstable)

### Consider

$$
|H(j\omega)| = \frac{1}{\sqrt{1 + \frac{\omega}{\omega_{c}}^{2k}}}
$$
- k is the order of the system

This is a candidate frequency response.

### Properties of This Candidate Frequency Response (Butterworth)

$$
\list{
      |H(j0)| = 1
      |H(j\infty)| = 0 High frequency gain that goes to 0!
      | H(j\omega) | > | H(j(\omega+\phi) |
      | H(j\omega_{c})| = \frac{1}{\sqrt{1 + 1}} = \frac{1}{\sqrt{2}}
      Note: |H(j\omega)| = \frac{1}{\sqrt{1 + \frac{\omega}{\omega_{c}}^{2k}}}
      = \sum_{h = 0}^{\infty}{[-\frac{\omega}{\omega_{c}}^{2k}]^{h}}
      = \frac{\omega}{\omega_{c}}^{2k} - \frac{\omega}{\omega_{c}}^{4k} \cdots
      (2k)(2k-1) \cdots (2k - (i - 1))\frac{\omega^{2k-i}}{\omega}
      }
$$


