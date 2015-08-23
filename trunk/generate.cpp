/////////////////////////////////////////////////
// This module generate an initial solution based on the hard constraints
// The main function is  void creRanSol(){}
// There is also an showSol function to show a solution.
//	After the searching, we also use it.
/////////////////////////////////////////////////
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"


// initial
int cover_h[7][5] = {0};
int nurseTotal = 0;


////////////////////////////////////////////////////////////
// search for every day
// step1: obtain the day's id, 1,2,3,...,0;Monday,...
// step2: based on the cover_h[dayId][j], search the every type to obtain how 
//		  many nurses in current day, saved in nurseSumT.
// step3: randomly select nurseSumT nurses saved in a[]
// step4: creating...
////////////////////////////////////////////////////////////
//void solutionCreate(){
void solutionCreate(char s[NURSE_NUM][DAY_NUM]){

	
	// 
	for(int i = 0; i < DAY_NUM; i++){ 
	
		// because the time interval begins from Friday
		int dayId = (i + startTimeOffset) % 7; // 
		//printf("%d\n", dayId);
	
		// loop cover_h to obtain nurse sum of current day
		int nurseSumT=0;
		for(int j = 0; j<TYPES; j++)nurseSumT = nurseSumT + cover_h[dayId][j];



		
		// ========== randomly select nurse  =========
		// the new method 
		int nurseIdxArray[NURSE_NUM] = {0}; // to hold the index number to choose
 		for(int idx = 0; idx < nurseTotal; idx++)nurseIdxArray[idx] = idx;
		
		int a[NURSE_NUM] = {0};	// hold the randomly selected nurse index

		int lastIdx = nurseTotal-1;

		//printf("num need is %d \n",nurseSumT);
		int selectedIdx = 0;
		for(int nurseNeed = 0; nurseNeed < nurseSumT; nurseNeed++){
 			selectedIdx = rand() % (nurseTotal - nurseNeed); // 0 ~ nurseTotal-1
			a[nurseNeed] = nurseIdxArray[selectedIdx];
			// half swap 
			nurseIdxArray[selectedIdx] = nurseIdxArray[lastIdx];
			lastIdx--;
			//printf("%d ",a[nurseNeed]);
 		}
		//printf("\n");

	
		
		// ===== creating based on the cover constraint and randoms in a[] ========
		int t3 = 0;
		for(int j = 0; j<TYPES; j++){   // for every type
			
			int t2 = cover_h[dayId][j]; // t2 is the needed nurse num in dayId of j type

			if( j == 0)
				for(int k = 0; k<t2; k++){ // k is for the num of times
					s[a[t3]][i] = 'E';
					t3++;
				}
			else if( j == 1)
				for(int k = 0; k<t2; k++){
					s[a[t3]][i] = 'L';
					t3++;
				}
			else if( j == 2)
				for(int k = 0; k<t2; k++){
					s[a[t3]][i] = 'D';
					t3++;
				}
			else if( j == 3)
				for(int k = 0; k<t2; k++){
					s[a[t3]][i] = 'N';
					t3++;
				}
			else if( j == 4)
				for(int k = 0; k<t2; k++){
					s[a[t3]][i] = 'H';
					t3++;
				}
		}

	}

	//solutionShow(s);

}