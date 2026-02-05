# Jan 28 2026

## Hilbert tansform
- Cannot be perfectly implemented (can be approxamated with a fair degree of accuracy though)

---

# 2.3 Ideal and Realizable Filters

## What is a low pas filter?

TODO  Refernce figure 2.14

- The evenness in the magnitute response yeilds a semetrical design

## Low Pass:

$$

H( \omega ) = \Pi ( frac{\omega}{2B} \\
Where B is bandwidth \omega_1 \\
h(t) = frac{B}{\Pi} sinc( frac{Bt}{\Pi} \\
zeros at frac{k \pi}{B}

$$

This is non - causaul therefor are not realizable. Comprimizes must always be made. To make causaul you can multiply by *u(t)*

## Figure 2.16

- If you increase the delay, you can approximate a closer filter.
- BiBo stability can never be ammended though.


## Another Idea | Windowing
Let x window be:

$$

x_w(t) = x(t) * W(t)

$$

with some possible windows being:
- $$ \Pi $$ Rectangular
- $$ \Lambda $$ Triangular

Now with Fouriear,

$$

X_w(t) = X( \omega ) * W(\omega)

$$

## Convolution

Use convolution

- KEY WORD: Respricol spresding

the main load will be inversly proportional to a lobe; the width (A) of a rectangular function.

- A triangle will have half the effecive with a triangle will be half of that with the rectangular funtion.

REMEMBER: Jump dicontinuity causes edges.
- So a triangle will have a derivative discontinuity (less ripple)
- the width of the lobe will be the width of the transition period in X_w(t)
- Smoother windows will have a larger delay (wider transition band)
- As filter complexity will produce more delay as well.


| windows       | Function | Lobe width | Roll off | peak side-lobe |
| ---------     | --       | ---        | --       | -----          |
| Rect \Pi(t/T) |          |            |          |                |
| Tri           |          |            |          |                |
| Hann          |          |            |          |                |
| Hamming       |          |            |          |                |
| Blackman      |          |            |          |                |
| Kaiser        |          |            |          |                |


