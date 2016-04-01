/* cldoc:begin-category(io.h)
* io.h defines file handling and printing functions.
*/


#ifndef __TESTH_IO__
#define __TESTH_IO__

#include "gen.h"

#include <stdio.h>

#define ON 	1
#define OFF	0

#define OK	1
#define ERR -1

enum TestHVerbosity {
	TestH_NONE 		= 0x0,
	TestH_LOW 		= 0x1,
	TestH_MEDIUM 	= 0x2,
	TestH_HIGH 		= 0x3
};

typedef enum TestHVerbosity verb;

extern verb TestHVerbosity;
extern int  TestHPrintPlain;
extern int  TestHPrintSep;
extern int  TestHPrintHeader;
extern int  TestHPrintMemCPU;
extern int  TestHEstPrintH;
extern int  TestHEstWrToFile;

//- http://www.ibm.com/developerworks/linux/library/l-tip-prompt/
#define CGRAY_GRAY  "\e[30;1;47m"
#define CRED_ORANGE "\e[33;1;41m"
#define CGRAY_BLUE  "\e[34;1;47m"
#define CRESET      "\e[0m"

#define TESTH_printVar(var) \
	fprintf(stdout, "%s", #var);


	//- --- Printouts ---

/* io_PrintTestH Function.
 *
 * io_PrintTestH prints to the standard output the TestH API summary.
*/
void io_PrintTestH ();


/* io_PrintInit Function.
 * @params executed comands.
 * @argv relative path to the directory where the executable have been generated.
 *
 * io_PrintInit prints to the standard output the executed commands, host name, user name,
 * current working directory and the relative path to the directory of the generated executable.
*/
void io_PrintInit (const char *params, const char *argv);


/* io_PrintDone Function.
 *
 * io_PrintDone prints to the standard output the executed commands, host name, user name,
 * current working directory and the relative path to the directory of the generated executable.
*/
void io_PrintDone ();

/* io_PrintSep Function.
 *
 * io_PrintSep prints to the standard output a message indicating that a process is done.
*/
void io_PrintSep ();

/* io_PrintError Function.
 * @err error number.
 * @format error information, accept multiple parameters.
 *
 * io_PrintError prints to the standard output an error message and it's details. The program continues
 * after this.
*/
void io_PrintError (const int err, const char *format, ...);

/* io_PrintErr Function.
 * @err error number.
 * @format error information, accept multiple parameters.
 *
 * io_PrintErr prints to the standard output an error message and it's details. The program exit
 * after this.
 *
*/
void io_PrintErr (const int err, const char *format, ...);

/* io_CheckH Function.
 * @h hurst exponent value to be checked.
 *
 * io_CheckH verifies if a certain given number is in the range of values of the Hurst Exponent.
 * @return "ERR" if h < 0.0 || h >= 1.0 otherwise returns "OK".
*/
int io_CheckH (double h);

/* io_CheckPowerOfTwo Function.
 * @num value to be checked.
 *
 * verifies if a given integer is a power of two.
 * @return return 1 if the given value is a power of two, otherwise returns 0.
*/
int io_CheckPowerOfTwo (int num);

/* io_CheckPowerOf Function.
 * @num value to be checked.
 * @exp exponent to be checked.
 *
 * io_CheckPowerOf verifies is a given integer is a power of a given value. 
 * Prints error message if parameters are invalid.
 * @return return "OK" if the given number is a power of the given exponent, otherwise return 0.
*/
int io_CheckPowerOf (int num, int exp);
// int io_PowerOfExp (int num, int exp);



	//- --- Files ---
/* io_FileOpen Function.
 * @path is the string which contains the path to the file.
 * @mode indicates in which mode a file should be opened.
 *
 * io_FileOpen open a file. Prints na error message if it fails.
 * @return return the pointer to the file stream if successful, otherwise returns NULL.
*/
FILE* io_FileOpen (const char *path, const char *mode);

/* io_FileClose Function.
 * @path is the string which contains the path to the file.
 * @f is theFILE pointer which we want to free.
 *
 * io_FileClose close a file. Prints na error message if it fails.
*/
void io_FileClose (const char *path, FILE *f);

/* io_FileClean Function.
 * @path is the string which contains the path to the file.
 *
 * io_FileClean deletes the content of a file. Creates a new file if it do not exist.
*/
void io_FileClean (const char *path);

/* io_FileLines Function.
 * @f is the FILE pointer from which we want to count the rows.
 *
 * io_FileLines counts the number of rows in a given file. Prients na error message if the FILE pointer is invalid.
 * @return number of lines in a given file.
*/
int io_FileLines (FILE *f);


int io_FileColumns (FILE *f);


int io_FileGetNum (FILE *f, double *p, gen g);

/* io_FileWr Function.
 * @path is the string which contains the path to the file.
 * @mode indicates in which mode a file should be opened.
 * @d1 is the first double value to be written.
 * @d2 is the second double value to be written.
 *
 * io_FileWr writes 2 double values to a file using the format "%lf %lf\n". 
*/
void io_FileWr (const char *path, const char *mode,
	const double d1, const double d2);

#endif /* __TESTH_IO__ */

/* cldoc:end-category(io.h) */