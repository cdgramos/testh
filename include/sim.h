/* cldoc:begin-category(sim.h) 
* sim.h provides generators which can simulate a certain kind of data
*/

#ifndef __TESTH_SIMULATORS__
#define __TESTH_SIMULATORS__

#include "proc.h"
#include "gen.h"


proc_Process* sim_NetworkTraffic (gen g, int n, double h, 
	int B, double L, int Imin, const char *pkts);


#endif /* __TESTH_SIMULATORS__ */

/* cldoc:end-category(sim.h) */