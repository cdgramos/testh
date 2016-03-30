/* cldoc:begin-category(est.h) 
* est.h provides estimators of the hurst parameter
*/

#ifndef __TESTH_ESTIMATORS__
#define __TESTH_ESTIMATORS__

#include "proc.h"

enum TestHEstimator { 
	TestH_RS	= 0x1,
	TestH_VT 	= 0x2,
	TestH_AMT	= 0x3,
	TestH_EBP	= 0x4
};

typedef enum TestHEstimator est;


/* est_RescaledRangeStatistics Function.
 * @pr is a pointer to a given process.
 *
 * est_RescaledRangeStatstics implements the Rescaled Range Statistics (R/S) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_RescaledRangeStatistics (proc_Process *pr);

/* est_VarianceTime Function.
 * @pr is a pointer to a given process.
 *
 * est_VarianceTime implements the Variance Time (VT) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_VarianceTime (proc_Process *pr);


void est_AbsoluteMomentsTime (proc_Process *pr, int mom);

void est_EmbeddedBranchingProcess (proc_Process *pr, int K);

#endif /* __TESTH_ESTIMATORS__ */

/* cldoc:end-category(est.h) */