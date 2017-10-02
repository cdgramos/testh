/* cldoc:begin-category(func.h) 
* func.h provides mathematical functions.
*/

#ifndef __TESTH_FUNCTIONS__
#define __TESTH_FUNCTIONS__

#include "dist.h"

/* func_complexNumber Structure.
 *
 * func_complexNumber defines a complex number.
 * @return complex number with real and imaginary part.
*/
typedef struct func_complexNumber{
	// real is the real part.
	double real;
	// imag is the imaginary part.
	double imag;
} func_complexNumber;

/* func_qsimp Function.
 * @d is the type of distribution to be considered.
 * @a is the lower closed interval boundary.
 * @b is the upper closed interval boundary.
 *
 * func_qsimp function performs a numerical integration of a function func over a closed interval [a,b] using the Simpson's rule.
 * @return the integral of the function func from a to b.
*/
double func_qsimp (dist d, double a, double b);

/* func_gammq Function.
 * @a is a scalar containing the value of the exponential of the gamma function.
 * @x is a scalar containing the upper limit of the integral of the incomplete gamma function.
 *
 * func_gammq function calculates the complement of the incomplete gamma function.
 * @return the complementary incomplete gamma function.
*/
double func_gammq (double a, double x);

/* func_FastFourierTransform Function.
 * @inputComplex array of complex numbers.
 * @n lenth of the arrays.
 * @temporaryComplex array of complex numbers.
 *
 * func_FastFourierTransform Applies the Fast Fourier Transform (FFT) to the array inputComplex, an empty array, temporaryComplex should also be passed as this is a recursive algorithm.
 * The value is overwritten on inputComplex memory.
*/
void func_FastFourierTransform (func_complexNumber *inputComplex, int n, func_complexNumber *temporaryComplex);



/* func_CumulativeSums Function.
 * @*x pointer to the array to compute the cumulative sums.
 * @*y pointer to the array that will contain the cumulative sums.
 * @xb mean of array x.
 * @N lenth of the arrays.
 *
 * func_CumulativeSums computer the cumulative sums of a time series (A.K.A. integrating the time series), and writes the results on array y.
*/
void func_CumulativeSums(double *x, double *y, double xb, int N);

#endif /* __TESTH_FUNCTIONS__ */

/* cldoc:end-category(func.h) */