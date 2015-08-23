///////////////////////////////////////////////////////////
// This file contains the function to evaluate an solution
// the loop order is first the nurses, then the days
//
// Max & Min working day			2	search and record the total 
// Max & Min consec working day		2	this part apply the new alg
// Max & Min consec free day		2
// ...........

// Max & Min consec working wkd		2
//
// Max working wkd in four weeks	1	record it
// No Night shift before free wkd  // just check
// alternative skill // this is also simple, just check it
//
//
///////////////////////////////////////////////////////////


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"



// output the evaluation information
//#define DEBUG

struct penaltyRec pRec = {0}; // the whole penalty

struct penaltyRec nursePenRec[NURSE_NUM] = {0};

int penArray[NURSE_NUM][DAY_NUM];


int evaluate(char s[NURSE_NUM][DAY_NUM]){

	
	for( int i = 0; i < nurseTotal; i++){
		nursePenRec[i].consecFree = 0;
		nursePenRec[i].consecWorkingday = 0;
		nursePenRec[i].consecWorkingWkd = 0;
		nursePenRec[i].maxwkd= 0;
		nursePenRec[i].pattern = 0;
		nursePenRec[i].shiftoff = 0;
		nursePenRec[i].threeWkd= 0;
		nursePenRec[i].dayoff= 0;
		nursePenRec[i].workingday= 0;
		nursePenRec[i].total= 0;

	}


	// reset the penalty array
	for( int i = 0; i < NURSE_NUM; i++ ){
		for( int j = 0; j < DAY_NUM; j++ ){
			penArray[i][j] = 0;
		}
	}
	
	//FILE* f_eva  = fopen("eva_output.txt", "w");
	// penalty reset
	int fitness = 0;
	
	int workingdayRec = 0;
	int consecWorkingdayRec= 0;
	int consecFreeRec= 0;
	int consecWorkingWkdRec= 0;
	int wkdRec= 0;
	int threeWkdRec= 0;
	int dayoffRec= 0;
	int shiftoffRec= 0;
	int patternRec= 0;
	int tempFit = 0;





	// =========================  for each nurse =========================
	for(int nurseIdx = 0; nurseIdx < nurseTotal; nurseIdx++){  
	//for(int nurseIdx = 0; nurseIdx < 1; nurseIdx++){  // for test
	//for(int nurseIdx = 1; nurseIdx < 2; nurseIdx++){  // for test
	//for(int nurseIdx = 49; nurseIdx < 50; nurseIdx++){  // for test
	
		nursePenRec[nurseIdx].idx = nurseIdx;

	
		// =========================  max min working day =========================
		tempFit = fitness;
		int maxf_t = contractArray[nursesContraMap[nurseIdx]].maxWorkDayOn;
		int minf_t = contractArray[nursesContraMap[nurseIdx]].minWorkDayOn;
		
		int max_t = contractArray[nursesContraMap[nurseIdx]].maxWorkDay;
		int min_t = contractArray[nursesContraMap[nurseIdx]].minWorkDay;
		
		int maxw_t = contractArray[nursesContraMap[nurseIdx]].maxWorkDayW;
		int minw_t = contractArray[nursesContraMap[nurseIdx]].minWorkDayW;
		
		int temp_workingday = 0;
		int total = 0;
		for(int i = 0; i < DAY_NUM; i++)
			if( s[nurseIdx][i] != 0)total++;
			
		if( maxf_t )
			if( total > max_t )	{
				fitness = fitness + ( total - max_t ) * maxw_t;
			}
 			 		
 		if( minf_t )
			if( total < min_t )fitness = fitness + ( min_t - total) * minw_t;
		
		workingdayRec += fitness - tempFit;
			
		nursePenRec[nurseIdx].workingday = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].workingday;
 	
		// test total
 		//printf(" cons is %d %d, total is %d, fit is %d\n",contractArray[nursesContraMap[nurseIdx]].maxWorkDay,
 		//	contractArray[nursesContraMap[nurseIdx]].minWorkDay,total, fitness);
		


		// =========================  consec working day =========================
 		maxf_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkDayOn;
		minf_t = contractArray[nursesContraMap[nurseIdx]].minConWorkDayOn;

		max_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkDay;
 		min_t = contractArray[nursesContraMap[nurseIdx]].minConWorkDay;
 		
		maxw_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkDayW;
 		minw_t = contractArray[nursesContraMap[nurseIdx]].minConWorkDayW;
		
		int workingCounter = 0;
		
		tempFit = fitness;
		for(int i = 0; i < DAY_NUM; i++){
			
			if( s[nurseIdx][i] != 0)workingCounter++;
			
			if ( s[nurseIdx][i] == 0 || i ==  DAY_NUM - 1 ) {
				if( workingCounter != 0 ){
					//compare
					if( maxf_t )
						if( workingCounter > max_t){
							fitness = fitness + (workingCounter - max_t)* maxw_t;
						}
					if( minf_t )
						if( workingCounter < min_t){
							fitness = fitness + (min_t - workingCounter)* minw_t;
						}//printf("working consec is %d\n", workingCounter);
				}
				workingCounter = 0;
			}
		}
		
		consecWorkingdayRec += fitness - tempFit; 

		nursePenRec[nurseIdx].consecWorkingday = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].consecWorkingday;



 		//printf(" cons is %d %d, weight is %d,  fit is %d\n",contractArray[nursesContraMap[nurseIdx]].maxConWorkDay,
 		//	contractArray[nursesContraMap[nurseIdx]].minConWorkDay, contractArray[nursesContraMap[nurseIdx]].maxConWorkDayW,fitness);
 		
		
		
		// =========================  consec free day =========================
		maxf_t = contractArray[nursesContraMap[nurseIdx]].maxConFreeOn;
		minf_t = contractArray[nursesContraMap[nurseIdx]].minConFreeOn;

		max_t = contractArray[nursesContraMap[nurseIdx]].maxConFree;
		min_t = contractArray[nursesContraMap[nurseIdx]].minConFree;

		maxw_t = contractArray[nursesContraMap[nurseIdx]].maxConFreeW;
		minw_t = contractArray[nursesContraMap[nurseIdx]].minConFreeW;
		
		int freeCounter = 0;
		tempFit = fitness ;
		for(int i = 0; i < DAY_NUM; i++){

			if( s[nurseIdx][i] == 0) freeCounter++;

			if ( s[nurseIdx][i] != 0 || i ==  DAY_NUM - 1 ) {
				if( freeCounter != 0 ){
					if( maxf_t )
						if( freeCounter > max_t){	
							fitness = fitness + (freeCounter - max_t)* maxw_t;
						}
					
					if( minf_t )
						if( freeCounter < min_t){
							fitness = fitness + (min_t - freeCounter)* minw_t;
						}
					
					//printf("free consec is %d\n", freeCounter);
				}
				freeCounter = 0;
			}
		}

		consecFreeRec += fitness - tempFit;
		
		nursePenRec[nurseIdx].consecFree = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].consecFree;

		
		
		// =========================  consec working wkd =========================
		tempFit = fitness;
		int weekArray[4] = {0}; 
		int wkdOffset = 0;
		if ( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 3)wkdOffset = 1; // sometime weekend is 3 day
				
		for(int i = (7-startTimeOffset-1) - wkdOffset; i < DAY_NUM; i+=7)			
			if( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 2){
				if( s[nurseIdx][i] != 0 || s[nurseIdx][i+1] != 0)weekArray[i/7] = 1;
			}
			
			else if( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 3 ){
				if( s[nurseIdx][i] != 0 || s[nurseIdx][i+1] != 0 || s[nurseIdx][i+2] != 0)weekArray[i/7] = 1;
			}
// 		for(int i = 0; i < 4; i++ ){
// 			printf("%d ", weekArray[i]);
// 		}
		


		maxf_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkWeekendOn;
		minf_t = contractArray[nursesContraMap[nurseIdx]].minConWorkWeekendOn;

		max_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkWeekend;
		min_t = contractArray[nursesContraMap[nurseIdx]].minConWorkWeekend;

		maxw_t = contractArray[nursesContraMap[nurseIdx]].maxConWorkWeekendW;
		minw_t = contractArray[nursesContraMap[nurseIdx]].minConWorkWeekendW;
		
		
		
		int workingWkdCounter = 0;
		
		for(int i = 0; i < 4; i++){
			
			if( weekArray[i] != 0)workingWkdCounter++;
			
			if ( weekArray[i] == 0 || i == 3 ) {
			
				if( workingWkdCounter != 0 ){
					
					if( maxf_t )
						if( workingWkdCounter > max_t)	fitness = fitness + (workingWkdCounter - max_t)* maxw_t;
					
					if( minf_t )
						if( workingWkdCounter < min_t)	fitness = fitness + (min_t - workingWkdCounter)* minw_t;
				}
				workingWkdCounter = 0;
			}
		}

		consecWorkingWkdRec += fitness - tempFit;

		nursePenRec[nurseIdx].consecWorkingWkd = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].consecWorkingWkd;


		
		
		// =========================  max working wkd =========================
		tempFit = fitness;
		int wkdtotal = 0;
		for(int i = 0; i < 4; i++ )wkdtotal += weekArray[i];
		//printf("total wkd is %d\n", wkdtotal);

		if(contractArray[nursesContraMap[nurseIdx]].maxWorkingWeekendOn){
			if( wkdtotal > contractArray[nursesContraMap[nurseIdx]].maxWorkingWeekend){
 				fitness = fitness + 
 					(wkdtotal - contractArray[nursesContraMap[nurseIdx]].maxWorkingWeekend)*
 					(contractArray[nursesContraMap[nurseIdx]].maxWorkingWeekendW);
			}
		}

		wkdRec += fitness - tempFit;

		nursePenRec[nurseIdx].maxwkd = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].maxwkd;

		

		// =========================  complete wkd =========================
		// =========================  identical complete wkd =========================
		// =========================  no night shift bf free wkd =========================
		// complete wkd, the penalties should be 2 - x of days, directly hash the penalty
		// if the wkd is 3, special case xox should be considered

		tempFit = fitness;
		wkdOffset = 0;
		
		int penalty_comp = 0;
		int penalty_ide = 0;
		int penalty_nn = 0;
		int comp_sum = 0;
		
		if ( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 3)wkdOffset = 1; // sometime weekend is 3 day

		// day from 0, thus 1 is Saturday, if 3 wkd day, 0 is Friday
		//for(int i = 4 - wkdOffset; i < DAY_NUM; i+=7){	// TODO
		for(int i = (7-startTimeOffset-1) - wkdOffset; i < DAY_NUM; i+=7){	
			if( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 2){	// 2 wkd days
				
				if( (s[nurseIdx][i] != 0 && s[nurseIdx][i+1] == 0) 
				||(s[nurseIdx][i] == 0 && s[nurseIdx][i+1] != 0) ) {			// not complete wkd
					penalty_comp++;
					comp_sum++;
				}

				else if( s[nurseIdx][i] == 0 && s[nurseIdx][i+1] == 0 ){	// check no night
					if( s[nurseIdx][i-1] == 'N' ){
						penalty_nn += 1;
					}
				}
				
				
				if(  s[nurseIdx][i] != s[nurseIdx][i+1] ){	// check for identical 
					
					if( s[nurseIdx][i] != 0 && s[nurseIdx][i+1] != 0 ){ // 2 different shifts
						penalty_ide += 2;
					}
					else	// a working and a free
						penalty_ide += 1;
					
				}				




			}
			else if( contractArray[nursesContraMap[nurseIdx]].wkdDayNum == 3 ){
				
				if( s[nurseIdx][i] != 0 && s[nurseIdx][i+1] == 0 && s[nurseIdx][i+2] != 0 ){
					// xox      penalty is 4 TODO to finish
					penalty_comp += 4;
					//penalty_comp += 2;
					//printf("penalty should be 4 in %d\n", i);
				}
				else if(s[nurseIdx][i] != 0 && s[nurseIdx][i+1] == 0 && s[nurseIdx][i+2] == 0){
					// xoo penalty is 2
					//printf("3 wkd day\n");
					penalty_comp += 2;
				}
				else if(s[nurseIdx][i] == 0 && s[nurseIdx][i+1] != 0 && s[nurseIdx][i+2] == 0){
					// oxo penalty is 2
					penalty_comp += 2;
				}
				else if(s[nurseIdx][i] == 0 && s[nurseIdx][i+1] == 0 && s[nurseIdx][i+2] != 0){
					// oox penalty is 2
					penalty_comp += 2;
				}
				else if(s[nurseIdx][i] != 0 && s[nurseIdx][i+1] != 0 && s[nurseIdx][i+2] == 0){
					// xxo  penalty is 1
					penalty_comp += 1;
				}
				else if(s[nurseIdx][i] == 0 && s[nurseIdx][i+1] != 0 && s[nurseIdx][i+2] != 0){
					// oxx penalty is 1
					penalty_comp += 1;
				}

				//printf("\n penalty_comp is %d\n ",penalty_comp);


				// check for identical
 				if( s[nurseIdx][i] != 0 || s[nurseIdx][i+1] != 0 || s[nurseIdx][i+2] != 0){
					//printf(" busy wkd in %d\n",i);
					
					// very complicated, hash again
					char c1,c2,c3; // temp vars for comparison 
					c1 = s[nurseIdx][i];
					c2 = s[nurseIdx][i+1];
					c3 = s[nurseIdx][i+2];

					if( c1 != 0 && c2 != 0 && c3 != 0){

						if(( c1 == c2 ) && ( c2 == c3 )  ){
							// no penalty
						}
						else if( ( c1 != c2) && ( c2 != c3) && ( c1 != c3) ){
							penalty_ide += 6;
						}
						else if(  (c1 == c2 &&  c2 != c3) || (c3 == c2 &&  c2 != c1) || (c1 == c3 &&  c2 != c1)){
							penalty_ide += 3;
						}

					}
					else if(  c1 == 0 &&  c2 != 0 && c3 != 0  ){
						if( c2 != c3 ){
							penalty_ide += 4;
						}
						else if( c2 == c3 ){
							penalty_ide += 1;
						}
					}

					else if(  c1 != 0 &&  c2 == 0 && c3 != 0  ){
						if( c1 != c3 ){
							penalty_ide += 4;
						}
						else if( c1 == c3 ){
							penalty_ide += 1;
						}
					}

					else if(  c1 != 0 &&  c2 != 0 && c3 == 0  ){
						if( c1 != c2 ){
							penalty_ide += 4;
						}
						else if( c1 == c2 ){
							penalty_ide += 1;
						}
					}

					// oox oxo xoo
					else if(  c1 == 0 &&  c2 == 0 && c3 != 0  ){
						penalty_ide += 2;
					}
					else if(  c1 != 0 &&  c2 == 0 && c3 == 0  ){
						penalty_ide += 2;
					}
					else if(  c1 == 0 &&  c2 != 0 && c3 == 0  ){
						penalty_ide += 2;
					}



					
// 					if( ( c1 == c2 ) && ( c2 == c3 ) ){
// 						// no penalty , it's identical
// 						//printf("identical wkd \n");
// 					}
// 					else if( ( c1 != c2 ) && ( c2 != c3 ) && ( c1 != c3 )){
// 						penalty_ide = +6;
// 						//printf(" p is 6 in %d\n", i);
// 					}
// 					else if( ( c1 == c2 ) && ( c1 != c3 )){
// 						penalty_ide = +3;
// 						//printf(" p is 3 in %d\n", i);
// 
// 					}
// 					else if( ( c1 != c2 ) && ( c2 == c3 )){
// 						penalty_ide = +3;
// 						//printf(" p is 3 in %d\n", i);
// 					}	
// 					else if( ( c1 != c2 ) && ( c1 == c3 )){
// 						penalty_ide = +3;
// 						//printf(" p is 3 in %d\n", i);
// 					}
			
				}
				
// 				else if(s[nurseIdx][i] == 0 && s[nurseIdx][i+1] == 0 && s[nurseIdx][i+2] == 0){
// 					// check for no night
// 					if( i != 0 ){ // the first day is Friday
// 						if( s[nurseIdx][i-1] == 'N'){
// 							penalty_nn = +1;
// 							//printf(" no night bf free wkd in %d\n", i);
// 						}
// 					}
// 				}

			
			}
		} // wkd loop	
		
		if(contractArray[nursesContraMap[nurseIdx]].idenShiftInWeekendOn)
			fitness = fitness + penalty_ide * contractArray[nursesContraMap[nurseIdx]].idenShiftInWeekendW;
		
 		//if(contractArray[nursesContraMap[nurseIdx]].noNSBfFWeekendOn)
 			//fitness = fitness + penalty_nn * contractArray[nursesContraMap[nurseIdx]].noNSBfFWeekendW;

		//printf("comp weight is %d %\n",contractArray[nursesContraMap[nurseIdx]].completeWeekendW);
		if(contractArray[nursesContraMap[nurseIdx]].completeWeekendOn)
			fitness = fitness + penalty_comp * contractArray[nursesContraMap[nurseIdx]].completeWeekendW;
		
		threeWkdRec += fitness - tempFit;
		//printf("comp sum is %d\n",comp_sum);

		nursePenRec[nurseIdx].threeWkd = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].threeWkd;



		//printf("\npenalty of comp is %d\n", penalty_comp);
		//printf("\npenalty of comp is %d\n", penalty_comp* contractArray[nursesContraMap[nurseIdx]].completeWeekendW);




		// =========================  alter =========================
		// search all the solution 
		// using nurseSkill[nurse num], if it is 2, no action
		// if it is 1 and is 'H', penalty. Normal nurse being a headnurse skill 
		//printf("skill level is %d \n", nurseSkill[nurseIdx]);

		if( nurseSkill[nurseIdx] != 2){
			for(int i = 0; i < DAY_NUM; i++)
				if( s[nurseIdx][i] == 'H'){
					//printf("not my work \n");
					// add penlty
					if(contractArray[nursesContraMap[nurseIdx]].alternativeOn){
						fitness += contractArray[nursesContraMap[nurseIdx]].alternativeW;
					//printf("altered \n");
					}
				}
		}
			

		// ========================= dayoff request =========================
		tempFit = fitness;
		for(int i = 0; i < DAY_NUM; i++){
			if(nurseDayoff[nurseIdx][i]){
				if( s[nurseIdx][i] != 0 ){
					//printf("day off in %d is \n", i);
					fitness++;
				}
			}
		} 

		dayoffRec += fitness - tempFit;
		
		nursePenRec[nurseIdx].dayoff = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].dayoff;

////		
//		
//		


//		// =========================  shift off request =========================
		// note that this is the new, multiple shift offs should be considered
		// nurseShiftoff[i][j][k], there are k shift types
		// nurseShiftoffNum[i][j] records the shift number
		tempFit = fitness;
		for(int i = 0; i < DAY_NUM; i++){
			if( nurseShiftoffNum[nurseIdx][i] ){
				//printf("number of shift off request %d\n ",nurseShiftoffNum[nurseIdx][i]);
				for( int shiftIdx = 0; shiftIdx < nurseShiftoffNum[nurseIdx][i]; shiftIdx++){
					//printf("type is %c\n",nurseShiftoff[nurseIdx][i][shiftIdx] );
					if( s[nurseIdx][i] == nurseShiftoff[nurseIdx][i][shiftIdx] ){
						fitness++;
					}
				}
			}
		}
		shiftoffRec += fitness - tempFit;
		nursePenRec[nurseIdx].shiftoff = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].shiftoff;


	

	



		// TODO test new
		// ========================= unwanted pattern =========================
		tempFit = fitness;
		for(int uwantedPatIndex = 0; uwantedPatIndex < contractArray[nursesContraMap[nurseIdx]].unWantPatTotal;
		uwantedPatIndex++ ){		// thus for each pattern. every nurse has a list of patterns. 

			for( int dayIndex = 0; dayIndex < 28 - unPatArray[uwantedPatIndex].shiftTotal + 1  ; dayIndex++){ 
 				
				bool notMatch = false;
				
				// the normal seq
				if(unPatArray[uwantedPatIndex].patSeq[0] != 'F'){
					
					for( int i = 0; i< unPatArray[uwantedPatIndex].shiftTotal; i++){
						if( s[nurseIdx][dayIndex+i] != unPatArray[uwantedPatIndex].patSeq[i]  ){
							notMatch = true;
							break;
						}
					}
					
					if(notMatch == false)
						fitness += unPatArray[uwantedPatIndex].patWeight;
					

				}
				
				// the wkd seq
				else if(unPatArray[uwantedPatIndex].patSeq[0] == 'F'){
					
					notMatch = false;// TODO

					if( (dayIndex + startTimeOffset)%7 == 5 ){
					
						
						if(s[nurseIdx][dayIndex] != 0) notMatch = true;
		
						// either of the two wkd day has a shift will conflict
						if(s[nurseIdx][dayIndex+1] == 0 && s[nurseIdx][dayIndex+2] == 0) notMatch = true;

						if(notMatch == false)
							fitness += unPatArray[uwantedPatIndex].patWeight;
					}
				}



 			}
 			
		
		
		
		}
		patternRec += fitness - tempFit;
		
		nursePenRec[nurseIdx].pattern = fitness - tempFit;
		nursePenRec[nurseIdx].total += nursePenRec[nurseIdx].pattern;





	}// the nurse loop



	
	// a global struct to record the specifics of the penalties
	pRec.workingday = workingdayRec;
	pRec.consecWorkingday = consecWorkingdayRec;
	pRec.consecFree = consecFreeRec;
	pRec.consecWorkingWkd = consecWorkingWkdRec;
	pRec.maxwkd = wkdRec;
	pRec.threeWkd = threeWkdRec;
	pRec.dayoff = dayoffRec;
	pRec.shiftoff = shiftoffRec;
	pRec.pattern = patternRec;

	//fclose(f_eva);
	//showPenaltySpec();

	return fitness;

}
