

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"



int holder[10] = {0};

int idx_6_10[210][6] = {0};


int sum = 0;

void comb(int a, int b){

	if ( a == 6 ) {
		
		for (int i =0; i<6; i++){
		//	printf("%d ",holder[i]);
			idx_6_10[sum][i] = holder[i];
		}
		//printf("\n");
		sum++;
			
		return; 
	}

	for ( int i = b + 1; i <= 10 - 6 + a + 1; i++)	{
		holder[a] = i;
		comb(a+1, i);
	}


} 




int main(void)
{
	initial();
	
	//comb(0,0);

	//printf("sum is %d",sum);

	//for (int i = 0; i < 210; i++){
	//	for (int j = 0; j < 6; j++)	{
	//		printf("%d ",idx_6_10[i][j]);
	//	}
	//	printf("\n");
	//}
	//getchar();



	experiment();



	// ---------- block start end test ---------------
	
	

// 	int s = (rand() % (5- 1 + 1)) + 1; // [1,5]
// 	int x1 = (rand() % ( (10-2*s) - 0 +1)) + 0;
// 	int x2 = x1 + s -1;
// 
// 	int y1 = (rand() % ( (10-s) - (x2+1) +1)) + (x2+1);
// 	int y2 = y1 + s -1;
// 	printf("step %d, x1 %d x2 %d, y1 %d y2 %d\n", s,x1,x2,y1,y2);


	// --------------- penalty test -----------------
	//Load("instance\\sprint04.txt");
	//char s[NURSE_NUM][DAY_NUM] = {0};
	//solutionCreate(s);
	//printf("value is %d", evaluate(s));
	//solutionRosterShowScreen(s);
	//getchar();
	//showPenaltySpec();
	//for( int i = 0; i < nurseTotal; i++)
	//	printf("nurse %d, total penalty is %d\n", nursePenRec[i].idx,nursePenRec[i].total);

	//
	////for( int i = 0; i < nurseTotal; i++)

	//printf("\n");
	//qsort(nursePenRec,NURSE_NUM,sizeof(nursePenRec[0]),cmp);

	//for( int i = 0; i < nurseTotal; i++)
	//	printf("nurse %d, total penalty is %d\n", nursePenRec[i].idx,nursePenRec[i].total);




	// --------------- compare -----------------
  	
	//Load("instance\\sprint04.txt");
 // 	char lv[NURSE_NUM][DAY_NUM] = {0};
 // 	solutionStandardRead(lv,"solutions\\zzrSolu_s04_59.txt");
	////solutionCreate(lv);

 // 	solutionRosterShowScreen(lv);
 // 	printf("value is %d", evaluate(lv));
 // 	showPenaltySpec();

	//for( int i = 0; i < nurseTotal; i++)
	//	printf("nurse %d, has a pen of workingday of %d\n", i,nursePenRec[i].workingday);
	//
	//for( int i = 0; i < nurseTotal; i++)
	//	printf("nurse %d, total penalty is %d\n", i,nursePenRec[i].total);


	//char zz[NURSE_NUM][DAY_NUM] = {0};
	//solutionStandardRead(zz,"solutions\\zzrSolu_s04_60.txt");
	//	solutionRosterShowScreen(zz);
	//printf("value is %d", evaluate(zz));
	//showPenaltySpec();
	//
	//for( int i = 0; i < nurseTotal; i++){
	//	printf("nurse %d, has a pen of workingday of %d\n", i,nursePenRec[i].workingday);
	//}

	//
	//printf("\ndistance of shift is %d", distanceShift(lv,zz));
	//printf("\ndistance of working day is %d", distanceWorkingDay(lv,zz));
	

	//int a[10];
	//randomNurseGen(a,10);

// 	int a[4];
// 	randomDayGen(a, 4);

	//--------------------------------- test solution create -------------------------------
	//char s[NURSE_NUM][DAY_NUM] = {0};
	//solutionCreate(s);


	//---------------------------------- search ------------------------
	//for(int i = 0; i < 1; i++)
	

	// read the optimal solution
 	//char s[NURSE_NUM][DAY_NUM] = {0};
 	//solutionRead(s);

	
	//printf("game over\n");
	//getchar();
	
	return 0;
	

}






