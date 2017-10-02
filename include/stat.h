/* cldoc:begin-category(stat.h) 
* stat.h provides statistical functions.
*/

#ifndef __TESTH_STATISTICS__
#define __TESTH_STATISTICS__

#include "proc.h"
#include "dist.h"

// http://www.danielmiessler.com/blog/the-craziest-thing-youll-ever-learn-about-pi
// 39 digits is enough
// But double cuts precision
#define PI 		(double) 3.141592653589793238462643383279502884197
#define PI2 	(double) 6.283185307179586476925286766559005768394
#define NEPER 	(double) 2.7182818284590452353602874713527

/* stat_Mean Function.
 * @pt set of points.
 *
 * stat_Mean function computes the Mean of the set pt and store it in pt->mean.
*/
void stat_Mean (proc_Points *pt);

void stat_AbsoluteMomentsTime (proc_Points *pt,	int e);

/* stat_StdDeviation Function.
 * @pt set of points.
 *
 * stat_StdDeviation function computes the Standard Deviation of the set pt and store it in pt->stdDev.
*/
void stat_StdDeviation (proc_Points *pt);

void stat_Variance (proc_Points *pt);

/* stat_Min Function.
 * @pt set of points.
 *
 * stat_Min returns the lowest point value in the set pt.
*/
double stat_Min (proc_Points *pt);

/* stat_Max Function.
 * @pt set of points.
 *
 * stat_Max returns the highest point value in the set pt.
*/
double stat_Max (proc_Points *pt);

double stat_Autovariance (proc_Points *pt, int k);

/* stat_Covariance Function.
 * @k first variable.
 * @h second variable.
 *
 * stat_Covariance quantifies the dependence between two variables, aka covariance.
 * @return the covariance between k and h.
*/
double stat_Covariance (int k, double h);

void stat_Autocorrelation (proc_Process *pr, int kmin, int kmax, double h);

/* stat_GOFKolmogorovSmirnov Function.
 * @pt set of points.
 * @d type of distribution.
 *
 * stat_GOFKolmogorovSmirnov applies the Goodness of Fit Kolmogorov-Smirnov to a set of points pt and to a certain distribution d.
 * This function prints to the standard output the computed value, which is a way to decide if a sample comes from a population with a specific distribution.
*/
void stat_GOFKolmogorovSmirnov (proc_Points *pt, dist d);

/* stat_GOFChiSquare Function.
 * @pt set of points.
 * @d type of distribution.
 *
 * stat_GOFChiSquare applies the Goodness of Fit Chi-Square to a set of points pt and to a certain distribution d.
 * This function prints to the standard output the computed value, which is a way to measure how well model data reflects the real data.
*/
void stat_GOFChiSquare (proc_Points *pt, dist d);

#endif /* __TESTH_STATISTICS__ */

/* cldoc:end-category(stat.h) */