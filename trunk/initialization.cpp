#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"




// the current solution
//char sol[NURSE_NUM][DAY_NUM]={0};



/////////////////////////////////////////
// constraints need to be loaded from the instance
////////////////////////////////////////
// cover constraint, which is one of the hard cons.
// '7' is the dayidx and 4 is the type that needed
// because the head nurse add, another shift type add, so the number is 5
//int cover_h[7][5] = {0};

//int nurseTotal = 0;

int nurseSkill[NURSE_NUM] = {0};

int nursesContraMap[NURSE_NUM];

int nurseDayoff[NURSE_NUM][DAY_NUM];

char nurseShiftoff[NURSE_NUM][DAY_NUM][10] = {0}; // weight is always 1
int nurseShiftoffNum[NURSE_NUM][DAY_NUM] = {0};		// mutiple shift off request, record the number




//int nurseShiftoff[NURSE_NUM][DAY_NUM][2];

contra contractArray[5] = {0};

char uPatterns[10][10] = {'F'}; 

//srand((unsigned)time(NULL)); 



void initial(){

//printf("\n  %d %d",rTestP1[0][0], nTest[3][1]);

	
	//uPatterns[10][10] = {0}; 
	
	// initialize the special pattern 
// 	uPatterns[2][0] = 3;
// 	uPatterns[2][1] = 'F';
// 	uPatterns[2][2] = 'A';
// 	uPatterns[2][3] = 'A';

	//char solution[NURSE_NUM][DAY_NUM];


}
