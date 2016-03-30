<<<<<<< HEAD
/* cldoc:begin-category(rng.h)
* rng.h defines random number generator functions.
*/

#ifndef __TESTH_RNG__
#define __TESTH_RNG__

/* rng_MT19937_sgenrand function.
 *
 * rng_MT19937_sgenrand defines a seed for the random number generator function "rng_MT19937_genrand".
*/
void rng_MT19937_sgenrand ();

/* rng_MT19937_genrand function.
 *
 * rng_MT19937_genrand random number generator using the standard Mersenne Twister algorithm.
 * @return returns a random double value.
*/
=======
#ifndef __TESTH_RNG__
#define __TESTH_RNG__


void rng_MT19937_sgenrand ();
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
double rng_MT19937_genrand ();



<<<<<<< HEAD
#endif /* __TESTH_RNG__ */

/* cldoc:end-category(rng.h) */
=======
#endif
>>>>>>> a2f70c1e6f868b8ea31e27bc0579de852bd519b0
