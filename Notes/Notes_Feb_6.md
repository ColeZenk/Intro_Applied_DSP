# Notes Febuary 6

Recall

$$
|H(j\omega)| = \frac{1}{\sqrt{1 + (\frac{\omega}{\omega_{c}})^{2k}}}
$$

refer to equation 2.38 and read the examples.

## Other Types of Filters
### A little history, the Chebychev filter.
Chebychev filters use a "fly fisherman" approach, i.e. buiding momentum before dropping.
- The Chebychev 1 only ripples in the pass band, 2 ripples in stop band.
- In many cases requires lower order.
- Sloppier, but thats good because it's in spec.


## Chebychev Type I
- Equal ripple
- out of pass band will enforce monotonic behavior

Consider normalized BB

$$
|H_{k}(\omega)|^{2} \frac{1}{1 + (\omega_{k})^{2}}
$$

Generalize to

$$
|H_{k}(\omega)|^{2} \frac{1}{1 + [F_{k}(\omega)]^{2}}
$$

Where F is a kth order polynomial. Take the reciproical.
- Reciporical of 1 is 1
- Reciporical of c^2 is c^-2


### Look a Lissajous Figure:

$$
x = cos(kt) \\
y =  cos(Kkt) \\
k = \frac{2\pi}{T} \\
y = cos(K arccos(x))
$$

This is representable as a polynomial in x. Chebychev polynomials.
