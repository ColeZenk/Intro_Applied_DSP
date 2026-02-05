# January 30th

Review

- Delay can improve accuracy
- Window functions can improve design

$$
h_\omega = h \times \omega \\\\
H_\omega = H \star \omega
$$

---

# Basic Filter Design
- Practical spec
- frequency transforms
  - LPF -> HP, BP, BS
  - LPF provides a good template for other filters
-

- We need to allow some ripple
  - Perfection is the enemy of finished
  - Oscillations can be beneficial
  - The oscillations can create momentum
  - Define a band gap that can be realistically satisfied
- For example, with radio, there must be gaps between frequencies
- Define 'gray zones' (tolerance for error)
- Simpler is always better and more maintainable (JUST GOOD ENOUGH)
- In IIR transition bands are often asymmetric
- High pass has the same as low pass
- Attenuation can be done as well (

$$
-20log_{10} |H_{lp}|\omega|
$$

---

# Transformation Rules
## What is a filter?
Something like

$$
H(s) = \frac{P(s)}{Q(s)}
$$

Can I make a LP into another LP? Yes, it allows you to reduce complexity. See normalized LPF design.
- Map ONE of your frequency, then everything else is stretched linearly.

- S --> kS
- S --> k/S
- It doesn't matter how the filters are stretched as long as they are within the bounds.

---

#  TODO
- [ ] Transcribe the LPF to BP ... etc formulas

