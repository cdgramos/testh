/* cldoc:begin-category(dist.h) 
* dist.h provides probability distribution functions.
*/

#ifndef __TESTH_DISTRIBUTIONS__
#define __TESTH_DISTRIBUTIONS__

#include "proc.h"

/* TestHDistribution Enumeration.
 *
 * TestHDistribution enumerates a list of possible distributions.
*/
enum TestHDistribution { 
	// The TestH_Unif is equivalent to value -1 and represents a Uniform Distribution.
	TestH_Unif		= -0x1,
	// The TestH_Gauss is equivalent to value 0 and represents a Gaussian Distribution.
	TestH_Gauss		= 0x0,
	// The TestH_Pareto is equivalent to value 1 and represents a Pareto Distribution.
	TestH_Pareto	= 0x1,
	// The TestH_Exp is equivalent to value 2 and represents a Exponential Distribution.
	TestH_Exp		= 0x2
};

typedef enum TestHDistribution dist;

/* dist_CheckDist Function.
 * @d is a distribution value to be checked if it is valid.
 *
 * dist_CheckDist verifies if a certain given distribution value belongs to the existing distribution enumeration.
 * @return "OK" if the value belongs to the enumeration, otherwise returns "ERR".
*/
int dist_CheckDist (dist d);

/* dist_PDFProb Function.
 * @d type of distribution.
 * @x input value for distribution functions.
 *
 * dist_PDFProb computes the Probability Density Function of distribution d..
 * @return the Probability Density Function value for a certain distribution d.
*/
double dist_PDFProb (dist d, double x);

/* dist_CDFProb Function.
 * @d type of distribution.
 * @x input value for distribution functions.
 *
 * dist_CDFProb computes the Cumulative Destribution Function of distribution d..
 * @return the Cumulative Destribution Function value for a certain distribution d.
*/
double dist_CDFProb (dist d, double x);

/* dist_UnifPDF Function.
 * @a first boundary of the interval.
 * @b second boundary of the interval.
 *
 * dist_UnifPDF calculates the Uniform Probability Density Function.
 * @return the Uniform Probability Density Function value for a certain interval.
*/
double dist_UnifPDF (double a, double b);

double dist_GaussPDF (double x, double mu, double sigma);
double dist_ParetoPDF (double x, double xm, double alpha);
double dist_ExponentialPDF (double x, double lambda);

double dist_UnifCDF (double x, double a, double b);
double dist_GaussCDF (double x, double mu, double sigma);
double dist_ParetoCDF (double x, double xm, double alpha);
double dist_ExponentialCDF (double x, double lambda);

double dist_UnifInv (double a, double b);
double dist_GaussBoxMuller ();
double dist_GaussPolar ();
double dist_ParetoInv (double xm, double alpha);
double dist_ExponentialInv (double lambda);

void dist_Buckets (proc_Points *pt, int b, double *x, double *y, 
	double *buck, int f);
double* dist_CDFIncremental (proc_Points *pt);

double dist_F (double Rsq, int pt);

#endif /* __TESTH_DISTRIBUTIONS__ */

/* cldoc:end-category(dist.h) */