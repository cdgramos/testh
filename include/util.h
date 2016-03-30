/* cldoc:begin-category(rng.h)
* rng.h defines general memory, time, sort and system functions.
*/

#ifndef __TESTH_UTILITIES__
#define __TESTH_UTILITIES__

#include <time.h>

/* util_MemMalloc Function.
* @num number of bytes to allocate.
*
* util_MemMalloc allocates a block of memory with the size of a given number using the Malloc function. Returns the pointer to the block.
*/
void* util_MemMalloc (size_t num);

/* util_MemCalloc Function.
* @num number of elements to allocate.
* @size size of each element.
*
* util_MemCalloc allocates a block of memory with the size of a given number using the Calloc function. Returns the pointer to the block.
*/
void* util_MemCalloc (size_t num, size_t size);

/* util_MemRealloc Function.
* @ p pointer to the block we want to reallocate.
* @ num new size of the memory block in bytes.
*
* util_MemRealloc rellocate a memory block  pointed by p.
*/
void* util_MemRealloc (void *p, size_t num);

/* util_MemFree Function.
* @p pointer to the block to be deallocated.
*
* util_MemFree free a memory block.
*/
void* util_MemFree (void *p);

void util_MemWr (long int B);

void util_TimeIt (clock_t *c);
void util_TimeWr (clock_t *start);
void util_TimeReset (clock_t *c);

/* util_Copy Function.
* @v origin memory block.
* @v2 destin memory block.
* @size number of elements to be copied.
*
* util_Copy copy the content of a memory block to another memory block.
*/
void util_Copy (double *v, double *v2, int size);

/* util_BubbleSort Function.
* @v pointer to the array.
* @size size of the array.
*
* util_BubbleSort sort na array using the bubble sort algorithm.
*/
void util_BubbleSort (double *v, int size);

/* util_GetHostname Function.
*
* util_GetHostname return the host name of the machine.
* @return return the host name of the machine.
*/
char* util_GetHostname ();

/* util_GetUsername Function.
*
* util_GetUsername return the username of the machine.
* @return return the username of the machine.
*/
char* util_GetUsername ();

/* util_GetCwd Function.
*
* util_GetCwd return current working directory.
* @return return current working directory.
*/
char* util_GetCwd ();

#endif /* __TESTH_UTILITIES__ */

/* cldoc:end-category(util.h) */