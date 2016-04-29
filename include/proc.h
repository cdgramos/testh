/* cldoc:begin-category(proc.h) 
* proc.h provides interfaces to manipulate processes.
*/

#ifndef __TESTH_PROCESS__
#define __TESTH_PROCESS__

/* TestHTypeOfSignal Enumeration.
 *
 * TestHTypeOfSignal defines the possible types of signal.
*/
enum TestHTypeOfSignal { 
	// The TestH_fGn is equivalent to value 1 and it represents the Fractional Gaussioan Noise.
	TestH_fGn 	= 0x1,
	// The TestH_fBm is equivalent to value 2 and it represents the Fractional Brownian Motion.
	TestH_fBm 	= 0x2
};

/* TestHTypeOfScale Enumeration.
 *
 * TestHTypeOfScale defines the possible types of scale.
*/
enum TestHTypeOfScale {
	// The TestH_INC is equivalent to value 1 and it represents an Incremental type of scale.
	TestH_INC	= 0x1,
	// The TestH_RAND is equivalent to value 2 and it represents a Random type of scale.
	TestH_RAND	= 0x2,
	// The TestH_POW is equivalent to value 3 and it represents a Potency type of scale.
	TestH_POW	= 0x3
};

typedef enum TestHTypeOfSignal tosig;
typedef enum TestHTypeOfScale  tos;


typedef struct {
	tos typeOfScale;

	unsigned int min;
	unsigned int max;
	unsigned int no;
	unsigned int mov;
	int *scales;
} proc_ScalesConfig;



typedef struct {
	double 				*points;
	double 				*times;
	unsigned int 		scale;
	unsigned long long 	size;

	tosig typeOfSignal;

	double mean;
	double stdDev;

	double amt;
	unsigned int moment;
} proc_Points;

typedef struct {
	proc_Points *scales;
	proc_ScalesConfig *conf;
} proc_Scales;

typedef struct {
	proc_Points *points;
	proc_Scales *scales;
	int scales_on;
	char *name;
} proc_Process;



proc_Process* proc_CreateProcess (const char *n, double *p, double *t, int s, 
	tosig sig);
proc_Points* proc_CreatePoints (double *p, double *t, int size, int scale, 
	tosig sig);

proc_ScalesConfig* proc_CreateScalesConfig (tos scl, int min, int max, int mov, 
	...);
void proc_CreateScales (proc_Process *pr, proc_ScalesConfig *conf);
void proc_CreateScalesTime (proc_Process *pr, proc_ScalesConfig *conf);

void proc_Aggregate (proc_Process *pr, int m);
void proc_Normalize (proc_Process *pr);
void proc_FractionalGaussianNoise (proc_Process *pr);
void proc_FractionalBrownianMotion (proc_Process *pr);

void proc_PrintProcessStruct (proc_Process *pr);

void proc_PrintHeader (proc_Process *pr);
void proc_PrintProcess (proc_Process *pr);
void proc_PrintScales (proc_Process *pr);
void proc_PrintPoints (proc_Points *pt);

void proc_DeleteProcess (proc_Process *pr);
void proc_DeleteScales (proc_Process *pr);
void proc_DeletePoints (proc_Points *pt);

int proc_CheckPoints (proc_Points *pt);
int proc_CheckScalesConfig (proc_ScalesConfig *conf);
int proc_CheckScales (proc_Scales *sl);
int proc_CheckProcess (proc_Process *pr);

void proc_PrintHeaderScales (proc_ScalesConfig *conf);

long int proc_SizeOfProcess (proc_Process *pr);


#endif /* __TESTH_PROCESS__ */

/* cldoc:end-category(proc.h) */