
/*!	\file		stats.c
	\author		Danielle Miike
	\date		2020-02-28
				This program performs several statistical calculations of data informed by the user or through a file and prints the result
	
*/

#define _CRT_SECURE_NO_WARNINGS

#include "array_t.h"
#include <math.h>
#include <stdio.h>
#include <ctype.h>


/*!	\method		swap
	\recieve	two double variables
	\return		void
	\Purpose	this method swap two variables */
void swap(double* pa, double* pb) {
	double hold = *pa;
	*pa = *pb;
	*pb = hold;
}

/*! \method		shell_sort
	\recieve	two arrays and the size of the arrays
	\return		void
	\Purpose	this method sort the array */

void  shell_sort(array_t arr1, array_t arr2, size_t size) {
	size_t stepSize = size / 2;
	while (stepSize > 0) {
		for (size_t idxLastInSegment = stepSize; idxLastInSegment < size; ++idxLastInSegment) {
			size_t idxCurrent = idxLastInSegment;
			while (idxCurrent >= stepSize && arr1.data[idxCurrent] < arr1.data[idxCurrent - stepSize]) {
				swap(&arr1.data[idxCurrent], &arr1.data[idxCurrent - stepSize]);
				swap(&arr2.data[idxCurrent], &arr2.data[idxCurrent - stepSize]);
				idxCurrent -= stepSize;
			}
		}
		stepSize /= 2;
	}
}

/***************************************************MEAN*************************************/
/*! \method		mean
	\recieve	one array and the size of the arrays
	\return		mean value
	\Purpose	this method calculates the mean of the array */
double mean(array_t arr, int size) {
	double meanValue = 0.0;
	for (int i = 0; i < size; i++) {
		meanValue += arr.data[i];
	}
	meanValue = meanValue / size;

	return meanValue;
}

/************************************************MEDIAN****************************************/
/*! \method		median
	\recieve	one array and the size of the arrays
	\return		median value
	\Purpose	this method calculates the median of the array */
double median(array_t arr, int size) {
	double medianValue = 0.0;

	// if number of elements are even
	if (size % 2 == 0)
		medianValue = (arr.data[(size - 1) / 2] + arr.data[size / 2]) / 2.0;

	// if number of elements are odd
	else
		medianValue = arr.data[size / 2];
	return medianValue;
}
/********************************************MODE**********************************************/
/*! \method		mode
	\recieve	a array to calc the mode, one array to store the modes and the size of the arrays
	\return		mode value(s)
	\Purpose	this method calculates the mode of the array */

int mode(array_t arr, array_t* modeArrayValue, int size) {
	int count = 1, modeFreq = 2, j = 0;
	double modeValue;

	for (int i = 0; i < size; i++) {
		for (j = i + 1; j < size; j++) {
			if (arr.data[i] == arr.data[j]) {
				++count;
			}
			else {
				break;
			}
		}
		if (count > 1 && count == modeFreq) {
			modeFreq = count;
			modeValue = arr.data[i];
			arrayPushBack(modeArrayValue, modeValue);
		}
		else if (count > modeFreq) {
			modeFreq = count;
			modeValue = arr.data[i];
			/*clear array*/
			arrayFree(modeArrayValue);
			/*fill array*/
			arrayPushBack(modeArrayValue, modeValue);
		}
		if ((modeFreq * (*modeArrayValue).nSize) == arr.nSize) {
			modeFreq = 0;
			arrayFree(modeArrayValue);
		}
		i = j - 1;
		count = 1;
	}
	
	if ((*modeArrayValue).nSize == 0){
		modeFreq = 0;
	}

	return modeFreq;
}
/***********************************************STD DEVIATION AND VARIANCE****************************************/
/*! \method		stdDev
	\recieve	one array, the size of the array and two variables to store the variance and the standart deviation
	\return		void
	\Purpose	this method calculates the variance and the standart deviation of the array */

void stdDev(array_t arr, int size, double* variance, double* stdDeviation) {
	double tempStdDev = 0;
	double meanValue = mean(arr, size);
	for (int i = 0; i < size; i++) {
		tempStdDev += (arr.data[i] - meanValue) * (arr.data[i] - meanValue);
	}
	*variance = tempStdDev / size;
	*stdDeviation = sqrt(tempStdDev / size);
}

/***************************************************ABSOLUTE DEVIATION********************************************/
/*! \method		absDeviation
	\recieve	one array, the size of the array and the value of mean, median or mode
	\return		a double
	\Purpose	this method calculates the variance and the standart deviation of the array */

double absDeviation(array_t arr, int size, double value){
	double abdDev = 0.0;
	double absSum = 0;
	for (int i = 0; i < size; i++) {
		
		if (arr.data[i] - value > 0) {
			absSum += (arr.data[i] - value);
		}
		else
			absSum += (arr.data[i] - value)*-1;
	}
	abdDev = absSum / size;
	return abdDev;
}
/*********************************************REGRESSION LINE ********************************************/
/*! \method		regressionLine
	\recieve	two arrays, the size of the array and two variables that will storage the results
	\return		void
	\Purpose	this method calculates the regression line */

void regressionLine(array_t* arr1, array_t* arr2, int size, double* a,double* b){
	double sum_xy = 0.0, sum_x = 0.0, sum_y = 0.0, sum_x2 = 0.0;
	for (int i = 0; i < size; i++) {
		
		sum_x += (*arr1).data[i];
		sum_y += (*arr2).data[i];
		sum_xy += (*arr1).data[i] * (*arr2).data[i];
		sum_x2 += pow((*arr1).data[i],2);
	}
	*b = (size * sum_xy - sum_x * sum_y) / (size * sum_x2 - pow(sum_x,2));
	*a = (sum_y - *b * sum_x) / size;
}
/********************************************************* Y at mid(X) **********************************/
/*! \method		midpoint
	\recieve	one array, the size of the array and one variable that will storage the result
	\return		void
	\Purpose	this method calculates the mid point of x*/
void midpoint(array_t arr, int size, double *x) {

	*x = (arr.data[0] + arr.data[size - 1]) / 2;	
}

/***********************************************************OUTLIERS**************************************/
/*! \method		outliers
	\recieve	two arrays, the size of the array, two empty arrays to storage the outliers, mean, standart deviation and the coeficient
				that will be 2 or 3
	\return		a integer
	\Purpose	this method calculates the outliers of a array and updated an array with the outliers*/
int outliers(array_t arr1, array_t arr2, int size, array_t* outlValArr1, array_t* outlValArr2, double mean, double stdDev,int coef) {
	int outQtd = 0;

	 // Verify if there is any outliers for Arr1
	for (int i = 0; i < arr1.nSize; i++) {
			if ( abs(mean - arr1.data[i]) >= stdDev* coef) {
				outQtd++;
				arrayPushBack(outlValArr1, arr1.data[i]);
				arrayPushBack(outlValArr2, arr2.data[i]);
			}
	}
	return outQtd;
}

/*************************************************PRINT MODE***************************************************/
/*! \method		printMode
	\recieve	two arrays and two frenquencies
	\return		void
	\Purpose	this method prints the mode(s)*/
void printMode(array_t modeArray1Value, array_t modeArray2Value, int freqArray1, int freqArray2) {
	
	printf("\nmode");

	if (freqArray1 == 0) {
		printf("%*s", 41, "no mode");
	}
	else {
		printf("%*s%d",40,"freq.=", freqArray1);
	}

	if (freqArray2 == 0) {
		printf("%*s", 20, "no mode");
	}
	else {
		printf("%*s%d", 19, "freq.=", freqArray2);
	}

	if (freqArray1 != 0) {
		for (int i = 0; i < modeArray1Value.nSize; i++) {
			printf("\n%45.6lf", modeArray1Value.data[i]);
		}
	}
	
	if (freqArray2 != 0) {
		if (freqArray1 != 0) {
			for (int i = 0; i < modeArray2Value.nSize; i++) {
				printf("%20.6lf", modeArray2Value.data[i]);
			}
		}
		else {
			for (int i = 0; i < modeArray2Value.nSize; i++) {
				printf("\n%60.6lf", modeArray2Value.data[i]);
			}
		}
	}
}

/***************************************PRINT ABS DEV MODE********************************************/
/*! \method		printAbsDevMode
	\recieve	two arrays, the size of the array and two arrays of mods
	\return		void
	\Purpose	this method prints the absolute deviation about the mode*/
void printAbsDevMode(array_t arr1, array_t arr2, int size, array_t modArray1, array_t modArray2) {
	
	printf("\n-> about the mode");
	if (modArray1.nSize == 0) {
		printf("%*s%", 28, "no mode");
	}
	else if (modArray1.nSize > 1) {
		printf("%*s%", 28, "multi-modal");
	}
	else {
		printf("%28.3lf", absDeviation(arr1, size, modArray1.data[0]));
	}

	if (modArray2.nSize == 0) {
		printf("%*s%", 20, "no mode");
	}
	else if (modArray2.nSize > 1) {
		printf("%*s%", 20, "multi-modal");
	}
	else {
		printf("%20.3lf", absDeviation(arr2, size, modArray2.data[0]));
	}	   
}
/***************************************PRINT OUTLIERS 2x ********************************************/
/*! \method		printOutliers2x
	\recieve	two arrays, the size of the array, two arrays of outliers, two means and two standart deviations
	\return		void
	\Purpose	this method prints the outliers when the standart deviation is * 2 */

void printOutliers2x(array_t arr1, array_t arr2, int size, array_t* outlValArr1, array_t* outlValArr2, double mean1, double mean2, double stdDev1, double stdDev2) {
	int outQtd, coef = 2;
	int space = 32;
	outQtd = outliers(arr1, arr2, size, outlValArr1, outlValArr2, mean1, stdDev1, coef);
	outQtd += outliers(arr2, arr1, size, outlValArr1, outlValArr2, mean2, stdDev2, coef);

	if (outQtd == 0) {
		printf("%*s%", space, "no outliers");
	}
	else {
		printf("%*s %-30.d", space, "# outliers =", outQtd);
		for (int i = 0; i < (*outlValArr1).nSize; i++) {
			printf(
				"\n%38.3lf %20.3lf", (*outlValArr2).data[i], (*outlValArr1).data[i]);
		}
	}
}
/***************************************PRINT OUTLIERS 3x ********************************************/
/*! \method		printOutliers3x
	\recieve	two arrays, the size of the array, two arrays of outliers, two means and two standart deviations
	\return		void
	\Purpose	this method prints the outliers when the standart deviation is * 3 */

void printOutliers3x(array_t arr1, array_t arr2, int size, array_t* outlValArr1, array_t* outlValArr2, double mean1, double mean2, double stdDev1, double stdDev2) {
	int outQtd, coef = 3;
	int space = 32;

	outQtd = outliers(arr1, arr2, size, outlValArr1, outlValArr2, mean1, stdDev1, coef);
	outQtd += outliers(arr2, arr1, size, outlValArr1, outlValArr2, mean2, stdDev2, coef);
	
	if (outQtd == 0) {
		printf("%*s%",space,"no outliers");
	}
	else {
		printf("%*s %-30.d", space, "# outliers =", outQtd);
		for (int i = 0; i < (*outlValArr1).nSize; i++) {
			printf("\n%38.3lf %20.3lf", (*outlValArr2).data[i], (*outlValArr1).data[i]);
		}
	}
}

/*******************************MAIN METHOD****************************************/
/*! \method		main
	\recieve	a file or user's imputs
	\return		a integer
	\Purpose	this method calculates and prints various statistical operations  */

int main(int argc, char* argv[]) {
	//declare the arrays using the structure create in header file
#if defined(_DEBUG)
	int dbgFlags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	dbgFlags |= _CRTDBG_CHECK_ALWAYS_DF;
	dbgFlags |= _CRTDBG_DELAY_FREE_MEM_DF;
	dbgFlags |= _CRTDBG_LEAK_CHECK_DF;
	_CrtSetDbgFlag(dbgFlags);
#endif
		
	array_t array1 = array();
	array_t array2 = array();
	char ch = ' ';
	int i = 0;

	double num1, num2;

	//declare a variable to recieve a file
	FILE* stream = stdin;

	if (argc > 2) {
		printf("Error: too many command-line arguments (%d)\n", argc);
		printf(
			"Usage: fcount [filename]\n"
			"\twhere filename is the name of a file.\n"
			"\tuses stdin if there is no filename.\n"
		);
		return EXIT_FAILURE;
	}
	//if it is a file open the file and read until end of file
	else if (argc == 2) {
		stream = fopen(argv[1] , "rb");

		while (fscanf(stream, "%lf,%lf", &num1, &num2) != EOF) {
			
			//fill the array and alocate more space if needed
			arrayPushBack(&array1, num1);
			arrayPushBack(&array2, num2);
		}	
	}

	else if (argc == 1) {
		//ask the user to input a list to perform the statistics
		printf("Enter a list of a comma-separated real number pairs terminated by EOF or non numeric input:\n");
		
		//read the inputs until it exists
		while (fscanf_s(stream, "%lf,%lf", &num1, &num2)) {
			
			// check is is end of file or a letter
			if (ch == EOF) {
				break;
			}
			// check if the next character is a space or end of line
			else if (isspace(ch) || ch == '\n') {
				while (isspace(ch) || ch == '\n')
					ch = getchar();
				ungetc(ch, stream);
			}
			else if (isalpha(ch))
			{
				printf("Invalid input. You should not enter a letter.\n");
				return 1;
			}
			//fill the array and alocate more space if needed
			arrayPushBack(&array1, num1);
			arrayPushBack(&array2, num2);
			}
	}

	// Sort the first array to perform the statistics methods
	shell_sort(array1, array2,array1.nSize);

	double array1Min = array1.data[0];
	double array1Max = array1.data[array1.nSize - 1];

	/****************************** MEAN ********************************************************************/
	double meanValueA1 = mean(array1, array1.nSize);
	/****************************** MEDIAN ******************************************************************/
	double medianValueA1 = median(array1, array1.nSize);
	/****************************** MODE *********************************************************************/
	array_t modeArr1Value = array();
	int freqModA1 = mode(array1, &modeArr1Value, array1.nSize);
	/****************************STD DEVIATION*****************************************************************/
	double varianceA1;
	double stdDeviationA1;
	stdDev(array1, array1.nSize, &varianceA1, &stdDeviationA1);
	/****************************ABSOLUTE MEAN DEVIATION*******************************************************/
	double absMeanDevA1 = absDeviation(array1, array1.nSize, meanValueA1);
	/****************************ABSOLUTE MEDIUN DEVIATION*****************************************************/
	double absMedianDevA1 = absDeviation(array1, array1.nSize, medianValueA1);
	/****************************ABSOLUTE MODE DEVIATION*****************************************************/
	double absDevModeArr1 = 0;
	if (modeArr1Value.nSize != 0 && modeArr1Value.nSize < 1) {
		absDevModeArr1 = absDeviation(array1, array1.nSize, modeArr1Value.data[0]);
	}
	/*******************************REGRESSION LINE**********************************************************/
	double a, b;
	regressionLine(&array1, &array2, array1.nSize, &a, &b);
	/***********************************MID POINT ********************************************************/
	double midArr1X, y;
	midpoint(array1,array1.nSize, &midArr1X);
	y = b * midArr1X + a;

	/******************************************** SORT ARRAY 2 *********************************************/
	shell_sort(array2, array1, array1.nSize);
	/****************************** MEAN ********************************************************************/
	double meanValueA2 = mean(array2, array2.nSize);
	/****************************** MEDIAN ******************************************************************/
	double medianValueA2 = median(array2, array2.nSize);
	/****************************** MODE *********************************************************************/
	array_t modeArr2Value = array();
	int freqModA2 = mode(array2, &modeArr2Value, array2.nSize);
	/****************************STD DEVIATION*****************************************************************/
	double varianceA2;
	double stdDeviationA2;
	stdDev(array2, array2.nSize, &varianceA2, &stdDeviationA2);
	/****************************ABSOLUTE MEAN DEVIATION*******************************************************/
	double absMeanDevA2 = absDeviation(array2, array2.nSize, meanValueA2);
	/****************************ABSOLUTE MEDIUN DEVIATION*****************************************************/
	double absMedianDevA2 = absDeviation(array2, array2.nSize, medianValueA2);
	/****************************ABSOLUTE MODE DEVIATION*****************************************************/
	double absDevModeArr2 = 0;
	if (modeArr1Value.nSize != 0 && modeArr1Value.nSize < 1) {
		absDevModeArr2 = absDeviation(array2, array2.nSize, modeArr2Value.data[0]);
	}

	/************************************ OUTLIERS *****************************************************/

	array_t outArr1 = array();
	array_t outArr2 = array();
	int out2xArr1Qtd, out3xArr1Qtd;

	/*******************************************PRINT*****************************************************/
	int space = -30;
	int spa = 9;
	int spa2 = 6;
	printf("stats (1.0.1), © 2020 Danielle Miike\n");
	
	printf("Results: ");
	printf("\n----------------------------------------------------------------------------");
	printf("\n%*s%15u%20u", space, "# elements",  array1.nSize, array2.nSize);
	printf("\n%*s%15.3lf%20.3lf", space, "minimun", array1Min, array2.data[0]);
	printf("\n%*s%15.3lf%20.3lf", space, "maximun", array1Max, array2.data[array2.nSize - 1]);
	printf("\n%*s%15.3lf%20.3lf", space, "mean", meanValueA1, meanValueA2);
	printf("\n%*s%15.3lf%20.3lf", space, "median", medianValueA1, medianValueA2);
	printMode(modeArr1Value, modeArr2Value, freqModA1, freqModA2);
	printf("\n%*s%15.3lf%20.3lf", space, "variance", varianceA1, varianceA2);
	printf("\n%*s%15.3lf%20.3lf", space, "stdDeviation", stdDeviationA1, stdDeviationA2);
	printf("\nmean absolute deviations:");
	printf("\n%*s%15.3lf%20.3lf", space, "-> about the mean", absMeanDevA1, absMeanDevA2);
	printf("\n%*s%15.3lf%20.3lf", space, "-> about the median", absMedianDevA1, absMedianDevA2);
	printAbsDevMode(array1, array2, array1.nSize, modeArr1Value, modeArr2Value);
	printf("\n%*s%*s%-15.3lf%*s%-10.3lf", space, "regression line",spa, "a= ", a, spa2,"b= ", b);
	printf("\n%*s%*s%-15.3lf%*s%-10.3lf", space,"Y at mid(X)",spa-1, "x= ", midArr1X,spa2, "y= ", y);
	printf("\nOutliers(2x)=");
	
	printOutliers2x(array1, array2, array1.nSize, &outArr1, &outArr2, meanValueA1, meanValueA2, stdDeviationA1, stdDeviationA2);
	
	arrayFree(&outArr1);
	arrayFree(&outArr2);

	printf("\nOutliers(3x)=");
	printOutliers3x(array1, array2, array1.nSize, &outArr1, &outArr2, meanValueA1, meanValueA2, stdDeviationA1, stdDeviationA2);

	/*****************************************************************************************************/
	/*FREE THE ARRAYS*/
	arrayFree(&modeArr1Value);
	arrayFree(&modeArr2Value);
	arrayFree(&outArr1);
	arrayFree(&outArr2);
	arrayFree(&array1);
	arrayFree(&array2);

	fclose(stream);
}



