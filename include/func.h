/* cldoc:begin-category(func.h) 
* func.h provides mathematical functions.
*/

#ifndef __TESTH_FUNCTIONS__
#define __TESTH_FUNCTIONS__

#include "dist.h"

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

#endif /* __TESTH_FUNCTIONS__ */

/* cldoc:end-category(func.h) */