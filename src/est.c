
#include "io.h"
#include "util.h"
#include "est.h"
#include "reg.h"
#include "dist.h"
#include "stat.h"
#include "func.h"

#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <sys/param.h>

#define TESTH_MAX 256

static char TestHEstFile[TESTH_MAX] = {'\0'}; 


static void est_Init (
	proc_Process *pr,
	est e,
	int res,
	int mom)
{
	char e1[50], e2[50];

	switch (e) {
		case TestH_RS:
			strcpy (e1, "RescaledRangeStatistics");
			strcpy (e2, "RS");
			break;
		case TestH_VT:
			strcpy (e1, "VarianceTime");
			strcpy (e2, "VT");
			break;
		case TestH_AMT:
			sprintf (e1, "AbsoluteMomentsTime %d", mom);
			strcpy (e2, "AMT");
			break;
		case TestH_EBP:				
			strcpy (e1, "EmbeddedBranchingProcess");
			strcpy (e2, "EBP");
			break;
		case TestH_HEAF:				
			strcpy (e1, "AutocorrelationFunction");
			strcpy (e2, "HEAF");
			break;
		case TestH_HIG:				
			strcpy (e1, "Higuchi");
			strcpy (e2, "HIG");
			break;
		case TestH_DFA:				
			strcpy (e1, "DetrendedFluctuationAnalysis");
			strcpy (e2, "DFA");
			break;
		case TestH_PER:				
			strcpy (e1, "Periodogram");
			strcpy (e2, "PER");
			break;

		default:
			strcpy (e1, "undefined");
			strcpy (e2, "undefined");
			break;
	}

	if (TestHEstWrToFile == ON) {
		memset (TestHEstFile, '\0', TESTH_MAX);
		strncpy (TestHEstFile, pr->name, strlen (pr->name));
		strncat (TestHEstFile, ".", 1);
		strncat (TestHEstFile, e2, strlen (e2));
		io_FileClean (TestHEstFile);
	}

	if (TestHVerbosity > TestH_NONE && TestHPrintPlain == OFF) {
		proc_PrintHeader (pr);
		fprintf (stdout, "%sESTIMATOR%s: %s -- %s\n",
			CGRAY_BLUE, CRESET, e1, e2);
		if (TestHEstWrToFile == ON && TestHPrintPlain == OFF)
			fprintf (stdout, " - EstWrToFile: ON\n");
		fprintf (stdout, "\n");
		if (res == ON && TestHVerbosity > TestH_MEDIUM && TestHPrintPlain == OFF)
			fprintf (stdout, "  scale\t\t ln(scale)\t ln(%s)\n", e2);
	}
}

static void est_PrintResult (
	int 	m,
	double 	lest)
{
	if (TestHVerbosity > TestH_MEDIUM) {
		if (TestHPrintPlain == OFF)
			fprintf (stdout, " %5d\t\t", m);
		fprintf (stdout, "%6.2lf\t\t%6.2lf\n", log (m), lest);
	}
	if (TestHEstWrToFile == ON)
		io_FileWr (TestHEstFile, "a", log (m), lest);
}

static void est_PrintH (
	est 	e,
	double 	h,
	double 	m,
	int 	mom)
{
	if (TestHVerbosity > TestH_NONE && TestHEstPrintH == ON) {
		if (TestHPrintPlain == ON)
			fprintf (stdout, "\t%lf\n", h);
		else {
			fprintf (stdout, "   d:\t\t\t\t= %lf\n", 2 - h);
			switch (e) {
				case TestH_RS:
					fprintf (stdout, "   H:\t\t\t\t= %.6lf\n", h); 
					break;
				case TestH_AMT:
					fprintf (stdout, "   H: 1.0 + %.2lf / %d\t\t= %.6lf\n", 
						m, mom, h);
					break;
				default:
					break;
			}
		}
	}
}


static double est_RescaledRangeStatisticsAux (
	proc_Points *fodp, // original points, first order differences process 
	proc_Points *pt)   // scale points
{    
	if (proc_CheckPoints (pt) == ERR || proc_CheckPoints (fodp) == ERR)
		io_PrintErr (ERR, "invalid proc_Points structure(s) in"
			" est_RescaledRangeStatisticsAux");

	int i, j, l, c;
	long double ds, min, max;
	long double ssum, rs_tot;

	for (i=0, rs_tot=0.0; i<pt->size; i++) {
		max = -DBL_MAX; min = DBL_MAX;
		ssum = 0.0;
		c = 0;
		for (j=0; j<pt->scale; j++) {
			ds = 0.0;
			for (l=pt->scale*i; l<=pt->scale*i+j && l<fodp->size; l++) {
				ds += fodp->points[l] - pt->points[i];
				if (j == pt->scale - 1) {
					c++;
					ssum += (fodp->points[l] * fodp->points[l]);
				}
			}
			// if (j == pt->scale-1 && abs (ds) != 0.0)
			// 	fprintf (stdout, "\t%d %d %d %Lf\n", l, pt->scale, j, ds);
			// fprintf (stdout, " %lf\n", ssum);
				// ssum = 0.0 many times on the normalized process of
				// the aggregation of renewal processes
				// below NaN is obtained because sqrt (0.0)
			if (ds < min) min = ds;
			if (ds > max) max = ds;
		}
		if (min == DBL_MAX)
			min = 0.0;
		if (max == -DBL_MAX)
			max = 0.0;
		long double stdDev = (long double) sqrt (ssum / (long double) c - 
			pt->points[i] * pt->points[i]);
			// stdDev == 0.0 ? 1.0 : stdDev;
		rs_tot += (max - min) / stdDev;
		/* fprintf (stdout, "\t%d %Lf %Lf %d %Lf %lf %Lf\n", 
			i, rs_tot, stdDev, c, ssum, pt->points[i] * pt->points[i],
			ssum / (long double) c - pt->points[i] * pt->points[i]); */
	}

	return rs_tot / pt->size;
}

double est_RescaledRangeStatistics (
	proc_Process *pr)
{
	if (proc_CheckProcess (pr) == ERR)
		io_PrintErr (ERR, "invalid proc_Process structure in"
			" est_RescaledRangeStatistics");
	
	clock_t c;
	util_TimeIt (&c);
	
	int s;
	double *y, *x;
	proc_Scales *scales;
	proc_Points *points;

	scales = pr->scales;
	x = (double*) util_MemMalloc (scales->conf->no * sizeof (double));
	y = (double*) util_MemMalloc (scales->conf->no * sizeof (double));

	est_Init (pr, TestH_RS, ON, -1);

	for (s=0; s<scales->conf->no; s++) {
		points = &scales->scales[s];
		
		double rs = log (est_RescaledRangeStatisticsAux (pr->points, points));
		if (isnan (rs)) {
			if (s == 0)
				y[s] = 0.0;
			else
				y[s] = y[s-1];
		}
		else 
			y[s] = rs;
		x[s] = log (points->scale);

		est_PrintResult (points->scale, y[s]);
	}

	reg_Linear *l = reg_LeastSquareMeans (y, x, scales->conf->no, ON);
	double Rsquared = reg_CoefficientOfDetermination (y, x, scales->conf->no);
	dist_F (Rsquared, scales->conf->no);

	double H = l->m;
	est_PrintH (TestH_RS, H, -1, -1);

	long int mem = sizeof (x) * scales->conf->no +
				sizeof (y) * scales->conf->no;
	util_MemWr (mem);
	util_MemFree (l);
	util_TimeWr (&c);
	return H;
}


static double est_AbsoluteMomentsTimeAux (
	proc_Process *pr,
	int 		 mom)
{
	clock_t c;
	util_TimeIt (&c);

	int s;
	double *x, *y;
	proc_Scales *scales; 

	scales = pr->scales;
	x = (double*) util_MemMalloc (scales->conf->no * sizeof (double));
	y = (double*) util_MemMalloc (scales->conf->no * sizeof (double));
	
	// stat_AbsoluteMomentsTime (pr->points, mom);
	// double y_o = log (pr->points->amt);

	for (s=0; s<scales->conf->no; s++) {
		stat_AbsoluteMomentsTime (&scales->scales[s], mom);
		y[s] = log (scales->scales[s].amt);
		x[s] = log (scales->scales[s].scale);
		printf("%lf\n", y[s]);
		est_PrintResult (scales->scales[s].scale, y[s]);
		// fprintf (stdout, " %lf\n", (y[s] - y_o) / (2 * x[s]) + 1);
	}

	reg_Linear *l = reg_LeastSquareMeans (y, x, scales->conf->no, ON);
	double Rsquared = reg_CoefficientOfDetermination (y, x, scales->conf->no);
	dist_F (Rsquared, scales->conf->no);

	// H = 1 + beta / mom
	double H = 1.0 + l->m / mom;
	est_PrintH (TestH_AMT, H, l->m, mom);

	long int mem = sizeof (x) * scales->conf->no +
				sizeof (y) * scales->conf->no;
	util_MemWr (mem);
	util_MemFree (l);
	util_TimeWr (&c);
	return H;
}


double est_VarianceTime (
	proc_Process *pr)
{
	if (proc_CheckProcess (pr) == ERR)
		io_PrintErr (ERR, "invalid proc_Process structure in"
			" est_VarianceTime");

	est_Init (pr, TestH_VT, ON, -1);

	return est_AbsoluteMomentsTimeAux (pr, 2);
}

double est_AbsoluteMomentsTime (
	proc_Process *pr,
	int 		 mom)
{
	if (proc_CheckProcess (pr) == ERR || mom <= 0)
		io_PrintErr (ERR, "invalid parameters in"
			" est_AbsoluteMomentsTime");

	est_Init (pr, TestH_AMT, ON, mom);

	return est_AbsoluteMomentsTimeAux (pr, mom);
}


static double est_CrossingLines (
	double 	delta,
	int 	k)
{
	return (double) delta * pow (2, k);
}

double est_EmbeddedBranchingProcess (
	proc_Process 	*pr,
	int 			K)
{
	if (pr->points == NULL || proc_CheckPoints (pr->points) == ERR)
		io_PrintErr (ERR, "invalid parameters in"
			" est_EmbeddedBranchingProcess");
	
	clock_t c;
	util_TimeIt (&c);
	est_Init (pr, TestH_EBP, OFF, -1);
 
	int p, k;
	int *crossings;
	double line, lastLineCrossed;
	// double delta;
	double *crossingLines;

	proc_Points *fGmPoints = pr->points;

	if (pr->points->typeOfSignal == TestH_fGn) {
		 //delta = pr->points->stdDev;
		 //fGmPoints = proc_fractionalBrownianMotion (pr->points);
		// not supposed to be commented
	}
	else if (pr->points->typeOfSignal == TestH_fBm) {
		proc_Points* fGnPoints = NULL; // = proc_fractionalGaussianNoise (pr->points);
		// not supposed to be commented
		// delta = fGnPoints->stdDev;
		util_MemFree (fGnPoints);
	}

	stat_StdDeviation (fGmPoints);

	lastLineCrossed = DBL_MAX;
	crossings = (int*) util_MemCalloc (K, sizeof (int));
	crossingLines = (double*) util_MemMalloc (K * sizeof (double));

	for (k=1; k<=K; k++) {
		crossingLines[k-1] = est_CrossingLines(2, k);
		fprintf (stdout, "line %d: %lf\n", k, crossingLines[k-1]);
	}

	fprintf (stdout, "\n");
	for (p=1; p<fGmPoints->size; p++) {
		for (k=1; k<=K; k++) {
			line = crossingLines[k-1];
			if (((fGmPoints->points[p-1] <= line &&
					fGmPoints->points[p] >= line) ||
				(fGmPoints->points[p-1] >= line &&
					fGmPoints->points[p] <= line)) &&
				line != lastLineCrossed) {
					
					//fprintf (stdout, "point %d crossed line %lf: %lf --> %lf\n",
					//	p, line, fGmPoints->points[p-1], fGmPoints->points[p]);
	
				lastLineCrossed = line;
				crossings[k]++;
				break;
			}
		}
	}

	fprintf (stdout, "\n");
	int cardinalitySum = 0;
	double uk, u = 0.0;
	double *x, *y;
	
	x = (double*) util_MemMalloc (K * sizeof (double));
	y = (double*) util_MemMalloc (K * sizeof (double));

	for (k=0; k<K; k++) {
		if (k < K - 1)
			uk = (double) crossings[k] / crossings[k+1];
		else
			uk = (double) crossings[k] / crossings[k];
		fprintf (stdout, "u_%d: %lf = %d / %d\n",
			k+1, uk, crossings[k], crossings[k+1]);
		
		u += (double) crossings[k] * uk;
		cardinalitySum += crossings[0];
		if(crossings[k-1] != 0) 
		x[k] = crossings[k] / crossings[k-1];
		y[k] = pow (2, k + 1);
	}

	u /= cardinalitySum;
	fprintf (stdout, "\n H = log (2) / log (%lf) = %lf\n",
		u, log (2) / log (u));

	reg_LeastSquareMeans (y, x, K, ON);
	double Rsquared = reg_CoefficientOfDetermination (y, x, K);
	dist_F (Rsquared, K);
	
	util_TimeWr (&c);

	return log (2) / log (u);
}




double est_AutocorrelationFunction (
	proc_Process 	*pr)
{
	if (proc_CheckProcess (pr) == ERR)
		io_PrintErr (ERR, "invalid proc_Process structure in"
			" est_AutocorrelationFunction");
	
	clock_t c;
	util_TimeIt (&c);

	est_Init (pr, TestH_HEAF, OFF, -1);
	
	//proc_Scales *scales = pr->scales;
	proc_Points *points = pr->points;

    int i = 0; // general purpose
    int k = 0; // general purpose

    double gamma_0 = 0.0;
    double gamma_1 = 0.0;
    double H = 0.0;


    stat_Mean(points);

    k = 0;
    for(i = 0; i < (points->size - k); i++){
        gamma_0 += (points->points[i] - points->mean) * (points->points[i + k] - points->mean);
    }
    gamma_0 = gamma_0 / points->size;

    k =1 ;
    for(i = 0; i < (points->size - k); i++){
        gamma_1 += (points->points[i] - points->mean) * (points->points[i + k] - points->mean);
    }
    gamma_1 = gamma_1 / points->size;

    H = 0.5 + (1 / (2 * log(2)) ) * log(1 + (gamma_1 / gamma_0));

    printf("\tH = %lf...\n",H);

    
	long int mem = sizeof (double);
	util_MemWr (mem);
	//util_MemFree (l);
	util_TimeWr (&c);
	//return H;
	return H;

}


double est_Higuchi (
    proc_Process    *pr)
{
    if (proc_CheckProcess (pr) == ERR)
        io_PrintErr (ERR, "invalid proc_Process structure in"
            " est_Higuchi");
    
    clock_t c;
    util_TimeIt (&c);

    est_Init (pr, TestH_HIG, OFF, -1);
 
    //proc_Scales *scales;
    proc_Points *points = pr->points;

    int i = 0;
    int j = 0;
    int h = 0;
    int k = 0;
    int acc = 0; 
    int val = 0; 
    int logBins = 0;
    int mlarge = 0;
    int n = 0; 
    int m = 0;
    int cutMin = 0;
    int cutMax = 0;

    double aux = 0.0; 
    double aux1 = 0.0; 
    double logMin = 0.0; 
    double logMax = 0.0; 
    double delta = 0.0; 
    double accDelta = 0;

    double *sequence = (double *) calloc(points->size + 1, sizeof(double));
    double *M; 
    double *curveLength;
    double **temp_lenght;

    int sizeM = 0;
    int sizeCurveLength = 0;
    int sizeTemp_lenght = 0;

    reg_Linear r;


    for(i = 1; i <= points->size; i++){
        aux = 0.0;
        for(j = 1; j <= i; j++){
            aux += points->points[j-1];
        }
        sequence[i] = aux;
    }

    mlarge = floor(points->size / 5); //5 is an empirical value!

    logMin = log10(1);
    logMax = log10(mlarge);
    logBins = 50; //empirical value
    delta = (logMax - logMin) / logBins;
    accDelta = 0;
    val = 0;
    j = -1;
    acc = 0;

    for (i = 1; i <= logBins; ++i) {
        accDelta += delta;
        val = (int)((pow(10, logMin + accDelta)));
        if (i == logBins) val = mlarge;
        if (j != val && val > 1) {
            j = val;
            acc++;
        }
    }
    n = acc;

    M = (double *) util_MemCalloc(n + 1, sizeof(double));
    sizeM = n + 1;

    j = -1;
    accDelta = 0;
    acc = 1;

    for (i = 1; i <= logBins; ++i){
        accDelta += delta;
        val = (int)((pow(10, logMin + accDelta)));
        if (i==logBins) val = mlarge;

        if (j != val && val > 1) {
            j = val;
            M[acc] = val;
            acc++;
        }
    }

    cutMin = ceil(n / 2);
    cutMax = floor(6 * n / 10);

    curveLength = (double *) util_MemCalloc(n + 1, sizeof(double));
    sizeCurveLength = n + 1;

    m = M[1];
    k = floor((points->size - m) / m);
    m = M[n];

    temp_lenght = util_MemMalloc( (m + 2) * sizeof(double *));

    for (i = 0; i <= m + 1; i++) {
        temp_lenght[i] = util_MemMalloc( (k + 2) * sizeof(double));
        sizeTemp_lenght += (k + 2);
    }

    for (h = 1; h <= n; h++) {
        m = M[h];
        k = floor((points->size - m) / m);
        aux = 0;
        for (i = 1; i <= m; i++) {
            aux1 = 0;
            for (j = 1; j <= k; j++){
                temp_lenght[i][j] = abs(sequence[i + j * m] - sequence[i + (j - 1) * m]);
                aux1 += temp_lenght[i][j];
            }
            aux1 /= k;
            aux += aux1;
        }
        curveLength[h] = aux * ((points->size - 1) / pow(m, 3));
    }


    for (i = 1; i <= n; i++) {
        M[i] = log(M[i]);
        curveLength[i] = log(curveLength[i]);
    }

    r = reg_LeastSquareMeansLimited(M, curveLength, cutMin, cutMax, OFF);

    printf("\n_______________________________\n\n");
    printf( "\tHurst = %.4lf\n_______________________________\n\n",2+r.b);





    long int mem = sizeof (sequence) * points->size + 
    			sizeof (M) * sizeM +
    			sizeof (curveLength) * sizeCurveLength +
    			sizeof (temp_lenght) * sizeTemp_lenght;
    util_MemWr (mem);
    util_TimeWr (&c);
 
    free(sequence);
    free(M); 
    free(curveLength);
    free(temp_lenght);
    
    return 2 + r.b;
}







double est_DetrendedFluctuationAnalysis (
    proc_Process    *pr)
{
    if (proc_CheckProcess (pr) == ERR)
        io_PrintErr (ERR, "invalid proc_Process structure in"
            " est_RescaledRangeStatistics");
    
    clock_t c;
    util_TimeIt (&c);

    est_Init (pr, TestH_DFA, OFF, -1);
    
    //proc_Scales *scales = pr->scales;
    proc_Points *points = pr->points;

    double boxratio = pow(2.0, 1.0 / 8.0); 
    int minWindow = 4;
    int maxWindow = points->size / 4;
    int totWindows = log10(maxWindow / (double)minWindow) / log10(boxratio) + 1.5;

    double *integrated;
    double *sequence;
    double *avgStdDeviation;
    double *windowSizes; 

    int potency = 1;

    double stat = 0.0;
    double size = 0.0;
    double sumFn = 0.0;
    double sumAux = 0.0;

    int i = 0;
    int j = 0;
    int z = 0;

    reg_Linear r;

    sequence = (double *) util_MemCalloc(points->size, sizeof(double));
    integrated = (double *) util_MemCalloc(points->size, sizeof(double));
    windowSizes = (double *) util_MemCalloc(totWindows, sizeof(double));
    avgStdDeviation = (double *) util_MemCalloc(totWindows, sizeof(double));


    stat_Mean(points);
    func_CumulativeSums(points->points, integrated, points->mean, points->size);


    windowSizes[0] = minWindow;
    for (i = 1; windowSizes[i - 1] < maxWindow; potency++) {
        size = minWindow * pow(boxratio, potency);
            if (size > windowSizes[i - 1]) {
                windowSizes[i] = size;
                i++;
            }
        if (i > totWindows) {
            windowSizes[i - 1] = maxWindow;
        }
    }

    totWindows = i;

    for (i = 0; i < points->size; i++) { 
        sequence[i] = i;
    }

    for (i = 0; i < totWindows; i++) {   

        stat = (double)(points->size / windowSizes[i]) * windowSizes[i];
        avgStdDeviation[i] = 0.0;
        sumFn = 0.0;
        sumAux = 0.0;

        for (j = 0; j <= points->size-windowSizes[i]; j += windowSizes[i]) {  
            r = reg_LeastSquareMeansLimited(sequence, integrated, j, j + windowSizes[i], OFF);

            for (z = j; z <= j + windowSizes[i]; z++) {  
                sumAux = integrated[z] - r.m - (r.b * z);
                sumFn += pow( sumAux ,2);
            }
        }

        avgStdDeviation[i] = sumFn / stat;
    }

    for (i = 0; i < totWindows; i++) { 
        windowSizes[i] = log10((double)windowSizes[i]);
        avgStdDeviation[i] = log10((double)avgStdDeviation[i]) / 2;
    }

    r = reg_LeastSquareMeansLimited(windowSizes, avgStdDeviation, 0, totWindows, OFF);

    printf("\n_______________________________\n\n");
    printf( "\tHurst = %.4lf\n_______________________________\n\n", r.b);


	long int mem = sizeof (sequence) * points->size +
                sizeof (integrated) * points->size +
				sizeof (windowSizes) * totWindows +
                sizeof (avgStdDeviation) * totWindows;
    util_MemWr (mem);

    free(sequence);
    free(integrated);
    free(avgStdDeviation);
    free(windowSizes);

    util_TimeWr (&c);

    return r.b;
}




double est_Periodogram (
	proc_Process 	*pr)
{
	if (proc_CheckProcess (pr) == ERR)
		io_PrintErr (ERR, "invalid proc_Process structure in"
			" est_RescaledRangeStatistics");
	
	clock_t c;
	util_TimeIt (&c);

	est_Init (pr, TestH_PER, OFF, -1);

	proc_Scales *scales = pr->scales;
	proc_Points *points = pr->points;

    int i = 0;

    double *x;
    double *y;

    int limit = (int) points->size / scales->conf->no; 


    func_complexNumber *complexVec = util_MemCalloc (points->size, sizeof(func_complexNumber));
    func_complexNumber *tmpComplexVec =  util_MemCalloc (points->size, sizeof(func_complexNumber));

    x =  util_MemCalloc((points->size / 2), sizeof(double));
    y =  util_MemCalloc((points->size / 2), sizeof(double));


    for (i = 0; i < points->size; i++) {
    	complexVec[i].real = points->points[i];
    }

    func_FastFourierTransform(complexVec, points->size, tmpComplexVec);

    for (i = 0; i < limit + 1; i++) {
        complexVec[i].real = pow(complexVec[i].real, 2);
        complexVec[i].imag = pow(complexVec[i].imag, 2);

        complexVec[i].real =  (complexVec[i].real + complexVec[i].imag) / (PI2 * points->size); 
    }

    for (i = 0; i < limit; i++) {
        x[i] = log((PI / points->size) * (i + 1));
    }

    for (i = 0; i < limit; i++) {
        if (complexVec[i + 1].real != 0.0) 
        	y[i] = log(complexVec[i + 1].real);
        else 
        	y[i] = log(0.0001);
    }

    reg_Linear r = reg_LeastSquareMeansLimited(x, y, 0, (int) points->size * 0.02, OFF);


    printf("\n_______________________________\n\n");
    printf( "\tHurst = %.4lf\n_______________________________\n\n", (1 - r.b) / 2);


	long int mem = sizeof (complexVec) * points->size +
				sizeof (tmpComplexVec) * points->size +
				sizeof (x) * (points->size / 2) +
				sizeof (y) * (points->size / 2);
	util_MemWr (mem);

	util_MemFree(complexVec);
	util_MemFree(tmpComplexVec);			
    util_MemFree(x);
    util_MemFree(y);

	util_TimeWr (&c);
	return ((1 - r.b) / 2);

}


