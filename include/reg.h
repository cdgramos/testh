<<<<<<< HEAD
/* cldoc:begin-category(reg.h)
* reg.h defines regression analysis functions and data types.
*/

=======
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
#ifndef __TESTH_REGRESSION__
#define __TESTH_REGRESSION__

typedef struct {
	double m;
	double b;
} reg_Linear;

<<<<<<< HEAD
/* reg_CoefficientOfDetermination Function.
 * @y is the pointer to the first data series. 
 * @x is the pointer to the second data series.
 * @n denotes the number of elements in the data series.
 *
 * reg_CoefficientOfDetermination calculates the Coefficient of Determination which depict the relationship between two data series.
 * @return the coefficient of correlation (range between 0 and 1) with 0 indication that the fata doesn't fit at all and 1 indicating a perfect fit.
*/
double reg_CoefficientOfDetermination (double *y, double *x, int n);

/* reg_LeastSquareMeans Function.
 * @y are the values for the y-axis.
 * @x are the values for the x-axis.
 * @n denotes the number of elements.
 * @print accept the values YES or NO to print the function result.
 *
 * reg_LeastSquareMeans calculates the overall solution that minimizes the sum of the squares of the errors.
 * @return returns the linear regression.
*/
=======
double reg_CoefficientOfDetermination (double *y, double *x, int n);

>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
reg_Linear* reg_LeastSquareMeans (double *y, double *x, int n, int print);



<<<<<<< HEAD
#endif /* __TESTH_REGRESSION__ */

/* cldoc:end-category(reg.h) */
=======
#endif
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
