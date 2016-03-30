<<<<<<< HEAD
/* cldoc:begin-category(batt.h) 
* batt.h provides batteries to compare various target hurst parameter values with the ones estimated for a defined generator.
*/

=======
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
#ifndef __TESTH_BATTERIES__
#define __TESTH_BATTERIES__

#include "proc.h"
#include "gen.h"



void batt_Generator (gen g, int n, int sim, double h1, double h2, double inc, 
	proc_ScalesConfig *conf);

void batt_Process (proc_Process *pr, proc_ScalesConfig *conf);

<<<<<<< HEAD
#endif /* __TESTH_BATTERIES__ */

/* cldoc:end-category(batt.h) */
=======
#endif
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
