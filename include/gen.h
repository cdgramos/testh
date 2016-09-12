/* cldoc:begin-category(gen.h) 
* gen.h provides generators of self-similar sequences.
*/

#ifndef __TESTH_GENERATORS__
#define __TESTH_GENERATORS__

#include "proc.h"

/* TestHGenerator Enumeration.
 *
 * TestHGenerator defines the available self-similar sequence generators.
*/
enum TestHGenerator { 
	// Extern Generator.
	TestH_EG		= -0x1,
	// Read File.
	TestH_RF		= -0x2,
	// Read File Matrix.
	TestH_RFM		= -0x3,
	// Read File Time.
	TestH_RFT		= -0x4,
	// Read File Time Aggregated.
	TestH_RFTA		= -0x5,

	// Gaussian.
	TestH_Gaussian	= 0x0,

	// Aggregation Renewals.
	TestH_AR 		= 0x1,
	// Fractional Brownian Motion Sequenctial Generation Algorithm.
	TestH_fBmSGA	= 0x2,
	// Simple Self Similar Process Generator.
	TestH_3SPG		= 0x3,
	// Hosking.
	TestH_Hosk		= 0x4,
	// Paxson.
	TestH_Pax		= 0x5
};

typedef enum TestHGenerator gen;

/* gen_PrintHeader Function.
 * @g generator.
 *
 * gen_PrintHeader function prints to the standard output the name of the generator g.
 * @return a proc_Process with a time series readen from a file.
*/
void gen_PrintHeader (gen g);

/* gen_ReadFile Function.
 * @g generator.
 *
 * gen_ReadFile function checks if a given generator g is valid..
 * @return OK if g is valir or ERR if g isn't valid.
*/
int gen_CheckGen (gen g);

proc_Process* gen_GenProc (gen g, int n, double h);

proc_Process* gen_ExternGen (int N, char *name, double (*gen_func) (void), 
	tosig sign);

/* gen_ReadFile Function.
 * @path path and file name.
 * @name desired process name (e.g. Hosking, Paxson, ...).
 * @sig is the type of signal we want to use.
 *
 * gen_ReadFile function reads a set of points from a file and return it as a process.
 * @return a proc_Process with a time series readen from a file.
*/
proc_Process* gen_ReadFile (const char *path, const char *name,
	tosig sig);

proc_Process* gen_ReadFileMatrix (const char *path, const char *name,
	tosig sig);

proc_Process* gen_ReadFileTime (const char *path, const char *name,
	tosig sig, int mult);


/* gen_Gaussian Function.
 * @N scalar defining the number of desired points to be generated.
 * @sig is the type of signal we want to use.
 *
 * gen_Gaussian function generates a time serie using the Gaussian algorithm.
 * @return a proc_Process with a generated time series of size N and with a hurst value of approximately 0.50.
*/
proc_Process* gen_Gaussian (int N, tosig sig);


proc_Process* gen_AggRenewal (int N, double h, int ren, int xm, tosig sig);


proc_Process* gen_fBmSequentialGenerationAlgorithm (int N, double h, 
	int scale_no, tosig sig);

proc_Process* gen_SimpleSelfSimilarProcessGenerator ();


/* gen_Hosking Function.
 * @N scalar defining the number of desired points to be generated.
 * @h target hurst value of the generated time series.
 * @sig is the type of signal we want to use.
 *
 * gen_Hosking function generates a self similar time serie using the Hosking algorithm.
 * @return a proc_Process with a generated time series of size N and with a hurst value of h.
*/
proc_Process* gen_Hosking (int N, double h, tosig sig);

/* gen_Paxson Function.
 * @N scalar defining the number of desired points to be generated.
 * @h target hurst value of the generated time series.
 * @sig type of signal to be used.
 *
 * gen_Paxson function generates a self similar time serie using the gen_Paxson algorithm.
 * @return a proc_Process with a generated time series of size N and with a hurst value of h.
*/
proc_Process* gen_Paxson  (int N, double h, tosig sig);

#endif /* __TESTH_GENERATORS__ */

/* cldoc:end-category(gen.h) */