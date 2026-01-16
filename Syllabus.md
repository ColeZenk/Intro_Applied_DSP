# ECE 444/644: Applied DSP and Filtering (3 Credits)
## Spring 2026 Course Information and Policies

**Last Updated:** January 14, 2026

---

## Instructor

**Dr. Roger A. Green**
- **Email:** Roger.Green@ndsu.edu
- **Office:** Offerdahl West 215B
- **Phone:** 231-1024
- **Office Hours:** 11:00–11:50 am MWF or by appointment

*Note: Email is the best contact method outside of class hours. Expect a reply within 24 hours (often much less).*

---

## Course Description

Digital signal processing theory balanced with practical application. Includes design of FIR, IIR, and adaptive filters; Fast Fourier transforms; sampling theory; implementation techniques; multi-rate processing. Emphasizes system implementation using development tools and DSP hardware: Keil uVision5 IDE and the Freescale FRDM-K22F. 

**Student projects, implemented in hardware, are required to pass the course.**

---

## Prerequisites

- ECE 173 (C-programming) AND
- ECE 343 (Signals and Systems)

OR course equivalents OR prior instructor approval.

---

## Required Text

- Lathi and Green, *Essentials of Digital Signal Processing*, Cambridge University Press, 2014.

---

## Supplemental Texts

- Porat, *A Course in Digital Signal Processing*, Wiley, 1997.
- Proakis and Manolakis, *Digital Signal Processing: Principles, Algorithms, and Applications*, 4th ed., Pearson, 2007.
- Van Valkenburg, *Analog Filter Design*, HRW Inc., 1982.
- Welch, Wright, and Morrow, *Real-Time Digital Signal Processing from MATLAB to C with the TMS320C6x DSK*, CRC Press, 2006.
- Freescale technical data sheets also provide valuable information.

---

## Lectures

**Time:** MWF 12:00-12:50  
**Location:** ECE 237

Lecture material is derived from class and supplemental texts, personal notes, etc. Attendance is expected and excused only through prior written approval from the instructor.

---

## Grading Breakdown

| Component | Weight | Details |
|-----------|--------|---------|
| **Homework, quizzes, and hardware assignments** | 50% | As assigned |
| **Midterm Exam** | 10% | Friday, March 24 |
| **Projects** | 25% | Proposal: Fri., Mar. 6<br>Progress report: Fri., Apr. 10<br>Final report & presentation: by Fri., May 8 |
| **Comprehensive Final Exam** | 15% | Tuesday, May 12, 3:30 pm – 5:30 pm |

### Grade Thresholds

- **A:** 90–100
- **B:** 80–90⁻
- **C:** 70–80⁻
- **D:** 60–70⁻
- **F:** <60

*Note: Grade thresholds may be lowered at the discretion of the instructor.*

---

## Homework

- Homework is due at the **beginning of class** on the due date.
- Neatly present homework solutions on **engineering paper**.
- **Staple** multiple sheets together.
- **Do not fold** your homework.
- A random selection of problems will be graded.
- **Late, illegible, or improperly formatted homework will not be given credit.**
- Some homework will require the use of Freescale tools (both software and hardware) as well as MATLAB.
- Frequently, demonstration of working hardware is required to receive assignment credit; thus, portions of homework and project grades are based on oral examination.

---

## Exams

- While exams will emphasize class material, homework, and laboratories, students are expected to apply concepts and techniques to new situations.
- During exams:
  - Books, notes, and homework are **normally not allowed**
  - Calculators and crib sheets are **normally permitted**

---

## Projects

Individual projects represent a major and important component of this course. **Each student is required to implement a DSP-based project in hardware to pass the course.**

### Project Requirements

1. **Personal Interest & Approval**
   - Projects must be in an area of personal interest to the student
   - Project topics require instructor approval
   - A formal memorandum proposing a project topic is due by **Friday, March 6**

2. **Progress Report**
   - Must be submitted by **Friday, April 10**
   - Should indicate project progress and what remains to be completed
   - Algorithm validation in MATLAB or C is highly recommended

3. **Hardware Implementation**
   - Projects must be implemented in hardware
   - Each student must demonstrate working hardware to the course instructor before **5:00 p.m., Friday, May 8**
   - A portion of each student's project grade will be based on hardware operability as well as oral questioning during project demonstration
   - A short presentation to the class may also be required

4. **Final Report**
   - Formal report documenting each project is due on **May 8**
   - Although length minimums are not specified, the report should be complete, professional, and reflective of the 25% grade weight (10 or more pages are likely necessary)
   - The report needs to include at least one (recent) reference that is a professional journal article or reputable conference article
   - *If you have any question whether your article qualifies, ask!*

---

## Graduate Credit (ECE 644)

While grading percentages are the same, students seeking graduate credit are required to:

1. Complete supplemental graduate-level questions on each assignment and exam
2. Complete projects reflective of the graduate level
3. Read supplemental journal literature and apply it to course work

### Additional Project Constraints for Graduate Students

4. **Thesis Connection**
   - Ideally, project topic should apply to the student's thesis interests
   - Project efforts should directly benefit the student's research

5. **Formal Presentation**
   - Graduate students must formally present their projects in a "lecture style" to the class
   - Presentation schedules and times will be provided later during the semester but will likely occur during the last week of class

6. **Enhanced Report Requirements**
   - Project reports must be written in a style consistent with a journal or conference paper submission
   - Must utilize at least **three separate references** to professional journal or reputable conference articles:
     - At least one reference must be from a significant journal article
     - At least one reference must have a publication date of **2025 or later**

---

## Academic Honesty

The academic community is operated on the basis of honesty, integrity, and fair play. 

**NDSU Policy 335: Code of Academic Responsibility and Conduct** applies to cases in which cheating, plagiarism, or other academic misconduct have occurred in an instructional context.

- Students found guilty of academic misconduct are subject to penalties, up to and possibly including suspension and/or expulsion
- Student academic misconduct records are maintained by the Office of Registration and Records
- Informational resources about academic honesty for students and instructional staff members can be found at [www.ndsu.edu/academichonesty](http://www.ndsu.edu/academichonesty)

**⚠️ Use of solutions manuals and online sites (e.g., Chegg) are prohibited and grounds for failing the course.**

---

## Special Needs and FERPA

Students with disabilities who need accommodations in this course are invited to share concerns or requests with the instructor and contact the Center for Accessibility and Disability Resources ([https://www.ndsu.edu/accessibility_disability](https://www.ndsu.edu/accessibility_disability)) as soon as possible. 

Your personally identifiable information and educational records as they relate to this course are subject to FERPA.

---

## Course Objectives

Upon successful completion of the course, students will be able to:

1. **Transform Analysis**: Perform time-domain, transform-domain, and frequency-domain analysis of continuous-time and discrete-time signals and systems, which includes use of the Laplace transform, the Fourier series, the Fourier transform, the z-transform, and the discrete-time Fourier transform.

2. **IIR Filter Design**: Design and digitally realize Butterworth, Chebyshev, inverse-Chebyshev, elliptic, and Bessel-Thomson IIR lowpass, highpass, bandpass, and bandstop filters, which includes the use of frequency response, pole/zero plots, frequency transformations, the impulse invariance method, the bilinear transform with prewarping, and block representations.

3. **Sampling Theory**: Utilize sampling theory to perform signal resampling and to properly convert continuous-time lowpass, bandpass, and non-bandlimited signals to their discrete-time counterparts and vice-versa, which includes utilizing analog-to-digital and digital-to-analog converter technologies.

4. **DSP Hardware**: Explain common DSP architectures, peripherals, hardware limitations and constraints and use the Freescale FRDM-K22F to realize digital signal processing systems.

5. **FIR Filter Design**: Design and digitally realize FIR lowpass, highpass, bandpass, and bandstop filters using the window design method, the frequency-sampling method, frequency-weighted least squares, and the Parks-McClellan algorithm, which includes an emphasis on the design and realization of linear phase FIR filter as well as block representations.

6. **DFT and FFT**: Compute the discrete Fourier transform using Goertzel's algorithm and the fast Fourier transform and utilize the DFT for linear convolution and filtering, which includes the application and use of zero-padding and circular convolution.

7. **CAD Tools**: Use modern computer-aided design and analysis tools such as MATLAB to solve digital signal processing problems.

8. **Project Implementation**: Identify, design, simulate, and hardware realize a digital signal processing system, which includes preparation and presentation of written and oral reports.

---

## Course Topics Schedule

| Session | Topic                                                                       |
|---------|-----------------------------------------------------------------------------|
| 1       | DSP introduction                                                            |
| 2       | CT signals and systems (review)                                             |
| 3       | FS, FT, and Laplace transforms (review)                                     |
| 4       | Frequency response and distortionless transmission                          |
| 5       | Ideal filters and data truncation by windows                                |
| 6       | Practical filter specification and analog filter transforms                 |
| 7       | Butterworth filter design                                                   |
| 8       | Chebyshev filter design                                                     |
| 9       | Inverse Chebyshev filter design                                             |
| 10      | Elliptic and Bessel-Thomson filters                                         |
| 11      | Feature overview of the Freescale FRDM-K22F and/or TI DSPs                  |
| 12      | Impulse sampling and practical sampling                                     |
| 13      | Ideal and ZOH signal reconstruction                                         |
| 14      | Sampling bandpass signals, spectral sampling                                |
| 15      | Quantization, coding, and ADC characteristics                               |
| 16      | Static and dynamic ADC errors, clock jitter                                 |
| 17      | ADC implementations, sample-and-hold considerations                         |
| 18      | DAC implementations                                                         |
| 19      | Architecture overview of Cortex M4 and/or TI processors                     |
| 20      | Overview FRDM-K22F and/or TI DSK peripherals, constraints                   |
| 21      | DT signals and systems (review), resampling                                 |
| 22      | DT analysis of DT systems (review)                                          |
| 23      | Discrete-time Fourier transform (DTFT)                                      |
| 24      | DTFT: system analysis and CTFT connection                                   |
| 25      | Digital processing of analog signals                                        |
| 26      | Resampling: frequency-domain perspective                                    |
| 27      | z-transforms                                                                |
| 28      | System realizations: DFI, DFII, TDFI, TDFII, parallel, cascade              |
| 29      | Frequency response of discrete-time systems                                 |
| 30      | Fixed-point considerations and Q format                                     |
| 31      | Introduction to digital filtering                                           |
| 32      | Digital IIR filter design: impulse invariance method                        |
| 33      | Digital IIR filter design: bilinear transform                               |
| 34      | Realization of digital IIR filters                                          |
| 35      | Linear-phase digital FIR filters, constraints                               |
| 36      | Digital FIR filter design: window design method                             |
| 37      | Digital FIR filter design: frequency-sampling method                        |
| 38      | Review linear vector spaces, orthogonality principle                        |
| 39      | Digital FIR filter design: frequency-weighted least squares                 |
| 40      | Equiripple FIR filters: Remez-exchange algorithm, Parks-McClellan algorithm |
| 41      | Discrete Fourier transform (DFT) and properties                             |
| 42      | Zero-padding and the DFT                                                    |
| 43      | Circular convolution, DFT-based linear convolution                          |
| 44      | Linear convolution: overlap-and-add method                                  |
| 45      | Linear convolution: overlap-and-save method                                 |
| 46      | Goertzel's algorithm                                                        |
| 47      | Polyphase decompositions and the fast Fourier transform (FFT)               |
| 48      | Decimation-in-time (DIT), decimation-in-frequency (DIF) FFTs                |
| 49      | Chirp FFT, discrete-cosine transform (DCT)                                  |
| 50      | Spectral analysis and advanced topics                                       |
