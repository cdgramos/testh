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
double rng_MT19937_genrand ();



#endif /* __TESTH_RNG__ */

/* cldoc:end-category(rng.h) */