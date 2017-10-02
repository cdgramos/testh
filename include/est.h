/* cldoc:begin-category(est.h) 
* est.h provides estimators of the hurst parameter.
*/

#ifndef __TESTH_ESTIMATORS__
#define __TESTH_ESTIMATORS__

#include "proc.h"

/* TestHEstimator Enumeration.
 *
 * TestHEstimator defines the available estimators.
*/
enum TestHEstimator { 
	// Rescaled Range Statistics.
	TestH_RS	= 0x1,
	// Variance Time.
	TestH_VT 	= 0x2,
	// Absolute Moments Time.
	TestH_AMT	= 0x3,
	// Embedded Branching Process.
	TestH_EBP	= 0x4,
	// Hurst Exponent by Autocorrelation Function.
	TestH_HEAF	= 0x5,
	// Higuchi.
	TestH_HIG   = 0x6,
	// Detrended Fluctuation Analysis.
	TestH_DFA   = 0x7,
	// Periodogram
	TestH_PER   = 0x8
};

typedef enum TestHEstimator est;


/* est_RescaledRangeStatistics Function.
 * @pr pointer to a given process.
 *
 * est_RescaledRangeStatstics implements the Rescaled Range Statistics (R/S) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_RescaledRangeStatistics (proc_Process *pr);

/* est_VarianceTime Function.
 * @pr pointer to a given process.
 *
 * est_VarianceTime implements the Variance Time (VT) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_VarianceTime (proc_Process *pr);


/* est_AbsoluteMomentsTime Function.
 * @pr pointer to a given process.
 * @mom number of absolute moments.
 *
 * est_AbsoluteMomentsTime implements the Absolute Moments Time (AMT) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_AbsoluteMomentsTime (proc_Process *pr, int mom);


/* est_EmbeddedBranchingProcess Function.
 * @pr is a pointer to a given process.
 * @K maximum number of crossing levels.
 *
 * est_EmbeddedBranchingProcess implements the Embedded Branching Process (EBP) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_EmbeddedBranchingProcess (proc_Process *pr, int K);


/* est_AutocorrelationFunction Function.
 * @pr pointer to a given process.
 *
 * est_AutocorrelationFunction implements the Hurst Exponent by Autocorrelation Function (HEAF) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_AutocorrelationFunction (proc_Process *pr);


/* est_Higuchi Function.
 * @pr pointer to a given process.
 *
 * est_Higuchi implements the Higuchi algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_Higuchi (proc_Process *pr);


/* est_DetrendedFluctuationAnalysis Function.
 * @pr pointer to a given process.
 *
 * est_DetrendedFluctuationAnalysis implements the Detrented Fluctuation Analysis(DFA) algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_DetrendedFluctuationAnalysis (proc_Process *pr);


/* est_Periodogram Function.
 * @pr pointer to a given process.
 *
 * est_Periodogram implements the Periodogram algorithm, and for a given process it returns the computed hurst parameter.
 * @return the hurst parameter for a given process.
*/
double est_Periodogram (proc_Process *pr);

#endif /* __TESTH_ESTIMATORS__ */

/* cldoc:end-category(est.h) */