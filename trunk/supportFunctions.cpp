// ==================================================
//	some support functions
// ==================================================

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"



// try for the day tabu
int const stepL = 15;
int dayRecord[stepL] = {0};
int nurseRecord[10]={0};
int randomInt[200] = {0};

int randomDayIdx[28] = {0};
int randomNurseIdx[10] = {0}; // 10 nurses, just for sprint track


void swap2Ints( int* a, int* b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}


int randIntInterval(int start, int end){
	
	assert(start <= end);
	return (rand()% ( end - start + 1) ) + start;

}


void randArray(int len){

	for(int i = 0; i < len; i++)randomInt[i] = i;

	int r;
	for(int i = 0; i < len; i++){
		r = rand()% (len-i);
		swap2Ints( &randomInt[r],&randomInt[len - i - 1]  );
	}

	//for(int i = 0; i < len; i++)printf("%d ",randomInt[i]);
	//printf("\n");

}
//

void randomDayGen(int holdArray[], int len){

	for(int i = 0; i < DAY_NUM; i++)randomDayIdx[i] = i;

	int r;
	for(int i = 0; i < DAY_NUM; i++){
		r = rand()% ( DAY_NUM-i );
		swap2Ints( &randomDayIdx[r],&randomDayIdx[ DAY_NUM - i - 1 ]  );
	}
	

	for(int i = 0; i < len; i++){
		holdArray[i] = randomDayIdx[i];
	}

//  	for(int i = 0; i < len; i++)
//  		printf("%d \n",holdArray[i]);

}

void randomNurseGen(int holdArray[], int len){
	
	for(int i = 0; i < 10; i++)randomNurseIdx[i] = i;

	int r;
	for(int i = 0; i < 10; i++){
		r = rand()% ( 10 - i );
		swap2Ints( &randomNurseIdx[r],&randomNurseIdx[ 10 - i - 1 ]  );
	}


	for(int i = 0; i < len; i++){
		holdArray[i] = randomNurseIdx[i];
	}

// 	  	for(int i = 0; i < len; i++)
// 	  		printf("%d \n",holdArray[i]);
}





// ========================= show functions  =========================

void showPop( struct Molecule pop[popSizeMax] ){
	
	static FILE* file_t = fopen("popShow.txt", "w+");
	
	for(int i = 0; i < currentPopSize; i++){
		//printf("%d ",MoleculePop[i].PE );	
		//fprintf(file_t, "%d ", MoleculePop[i].PE );	
		fprintf(file_t, "%d ", pop[i].PE );	
		
	}
	
	fprintf(file_t,"\n");
	fflush(file_t);
	fclose(file_t);
}



// show 2d view
void solutionRosterShowScreen( char s[][DAY_NUM]){

	printf(" ");

	for(int j = 0; j < DAY_NUM; j++){

		if(j<10){
			if( j % 7 == (7-startTimeOffset+1) )
				printf("  %d",j);
			else
				printf(" %d",j);
		}
		else{
			if( j % 7 == (7-startTimeOffset+1) )
				printf(" %d",j);
			else 
				printf("%d",j);
		}
	}

	printf("\n");

	for(int i = 0; i < nurseTotal; i++){
		
		printf("%d ",i);

		for(int j = 0; j < DAY_NUM; j++){
			printf("%c ",s[i][j]);
			//printf("%d ",solution[i][j]);
			if( j%7 == 7-startTimeOffset )printf("|");
		}
		printf("\n");
	}
}




// show the standard solution style
void solutionStandardOutputFile( char s[][DAY_NUM]){

	//FILE *sol_fout_eva = fopen("zzrSolu.txt", "w");
	FILE *sol_fout_eva = fopen("E:\\main_res\\working\\paper project\\roster project\\evaluator\\zzrSolu.txt", "w");
	//FILE *sol_fout_eva = fopen("zzrSolu.out", "w");
	//printf("errno[%d][%s]\n",errno,strerror(errno));	
	assert(sol_fout_eva != NULL);
	
	int sum = 0;
	for(int j = 0; j < DAY_NUM; j++){
		for(int i = 0; i < nurseTotal; i++){
			if(s[i][j]){
				sum++;
			}
		}
		//printf("\n");
	}

	//static FILE *sol_fout_eva = fopen("zzrSolu_show.txt", "w+");

	fprintf(sol_fout_eva,"////////////////////////////////////////////////////////////////////\n");
	//fprintf(sol_fout_eva,"SOLUTION = %s;\n",instAttri.instanceName);  // TODO modify 
	fprintf(sol_fout_eva,"SOLUTION = ");  // TODO modify 
	
	int cIdex = 0;
	while( instAttri.instanceName[cIdex] !=',' ){
		fprintf(sol_fout_eva,"%c",instAttri.instanceName[cIdex]);  // TODO modify 
		cIdex++;
	}
	fprintf(sol_fout_eva,";\n");  // TODO modify 

	
	
	fprintf(sol_fout_eva,"////////////////////////////////////////////////////////////////////\n");
	fprintf(sol_fout_eva,"ziran,  00;\n");  // TODO modify
	fprintf(sol_fout_eva,"\n");
	fprintf(sol_fout_eva,"\n");
	fprintf(sol_fout_eva,"////////////////////////////////////////////////////////////////////\n");
	fprintf(sol_fout_eva,"ASSIGNMENTS = ");  
	fprintf(sol_fout_eva,"%d;\n",sum);  
	fprintf(sol_fout_eva,"////////////////////////////////////////////////////////////////////\n");

	int mon = 0;
	if( !strcmp(instAttri.instanceStartTime,"2010-01-01,") ){
		mon = 1;
	}
	else if( !strcmp(instAttri.instanceStartTime,"2010-06-01,") ){
		mon = 6;

	}

	for(int j = 0; j < DAY_NUM; j++){
		for(int i = 0; i < nurseTotal; i++){
			if(s[i][j]){

				if(j < 9)
					fprintf(sol_fout_eva,"2010-0%d-0",mon);
				else
					fprintf(sol_fout_eva,"2010-0%d-",mon);

				fprintf(sol_fout_eva,"%d,",j+1);

				if(s[i][j] == 'H'){
					fprintf(sol_fout_eva," %d, D%c;\n",i,s[i][j]);
				}
				else
					fprintf(sol_fout_eva," %d, %c;\n",i,s[i][j]);


			}
		}
		//printf("\n");
	}

	
	
	// TODO modify TODO use the Medium to exclude the three
	fprintf(sol_fout_eva,"////////////////////////////////////////////////////////////////////\n");


	//printf("%d",sum);



	fflush(sol_fout_eva);
	fclose(sol_fout_eva);

}




// show the 2d view
void solutionShowTofile( char s[][DAY_NUM]){
	
	FILE *sol_fout = fopen("solutionTmp.txt", "w");
	
	for(int i = 0; i < nurseTotal; i++){
		for(int j = 0; j < DAY_NUM; j++){
			fprintf(sol_fout,"%c",s[i][j]);
			//printf("%d ",solution[i][j]);
			//if( j%7 == 2 )fprintf(sol_fout,"|");
		}
		fprintf(sol_fout,"\n");
	}
	fflush(sol_fout);
	fclose(sol_fout);
}





// ========================= solution related =========================

void solCopy(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]){
	for (int i = 0; i < NURSE_NUM ; i++){
		for (int j = 0; j < DAY_NUM ; j++){
			a[i][j] = b[i][j];
		}
	}
}


// for some log
void solutionReadof53(char s[NURSE_NUM][DAY_NUM] ){


	static FILE* fin_53;

	errno_t err;
	err =  fopen_s(&fin_53,"solutionTmpForRead.txt", "r");
	char tmp;

	for(int i = 0; i < NURSE_NUM; i++){
		for(int j = 0; j < DAY_NUM; j++){
			fscanf_s(fin_53,"%c",&s[i][j]);
			//printf("%d ",solution[i][j]);
			//if( j%7 == 2 )fprintf(sol_fout,"|");
		}
		fscanf_s(fin_53,"%c",&tmp);

		//fprintf(sol_fout,"\n");
	}
	
	//fscanf_s(solRead,"%s",tmp, 500);


}





// ========================= operators =========================
void swap2shifts( char* a, char* b){
	char tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}









void randNurIdx(){
	
	for(int i = 0; i<10; i++){
		nurseRecord[i]=i;
		//printf("%d ",nurseRecord[i]);
	}

	int r;
	int tmp;
	
	for(int i = 0; i<10; i++){
		r = rand() % (10-i);
		
		tmp = nurseRecord[9-i];
		nurseRecord[9-i] = nurseRecord[r];
		nurseRecord[r] = tmp;

	}


	//for(int i = 0; i<10; i++){
	//	printf("%d ",nurseRecord[i]);
	//}


}





void singleShiftSwap(char sol[NURSE_NUM][DAY_NUM]){
	int d = rand()% DAY_NUM;
	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;
	while ( (sol[n1][d] == sol[n2][d]) )n2 = rand()% nurseTotal;

	char temp;
	temp = sol[n1][d];
	sol[n1][d] = sol[n2][d];
	sol[n2][d] = temp;
}


//void multiNurseSingleDaySwap(char sol[NURSE_NUM][DAY_NUM]){
//
//	int dayIdx = rand()% DAY_NUM;
//
//	for( int nurseIdx = 0; nurseIdx < 5; nurseIdx++){
//		swap2shifts( &sol[nurseIdx][dayIdx], &sol[nurseIdx+5][dayIdx]);
//	}
//
//}



void twoNurseMultiDaySwap(char sol[NURSE_NUM][DAY_NUM], int dayNum){


	int randIdx[28];
	randomDayGen(randIdx, 28);


 	int n1 = rand()% nurseTotal;
 	int n2 = rand()% nurseTotal;
 	while ( n1 == n2 )
 		n2 = rand()% nurseTotal;

	
	for (int i = 0; i < dayNum; i++)
		swap2shifts(&sol[n1][randIdx[i]], &sol[n2][randIdx[i]]);
	
}


void cycle3nurse(char sol[NURSE_NUM][DAY_NUM]){

		
	randNurIdx();
	int n1 = nurseRecord[0];
	int n2 = nurseRecord[1];
	int n3 = nurseRecord[2];
	int d = rand()% DAY_NUM;


	swap2shifts(&sol[n1][d], &sol[n2][d]);
	swap2shifts(&sol[n1][d], &sol[n3][d]);
	

}


// swap two working shifts
void singleWorkingDaySwap(char sol[NURSE_NUM][DAY_NUM]){

	int d = rand()% DAY_NUM;
	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;

	while ( (sol[n1][d] == sol[n2][d]) || ((sol[n1][d] != 0)&&(sol[n2][d] == 0)) ||
		((sol[n1][d] == 0)&&(sol[n2][d] != 0))){
			n1 = rand()% nurseTotal;
			n2 = rand()% nurseTotal;
	}
		
	char temp;
	temp = sol[n1][d];
	sol[n1][d] = sol[n2][d];
	sol[n2][d] = temp;
}


void singleWorkingDayMove(char sol[NURSE_NUM][DAY_NUM]){
	
	int d = rand()% DAY_NUM;
	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;

	while ( (sol[n1][d] == 0)&&(sol[n2][d] == 0) || (sol[n1][d] != 0)&&(sol[n2][d] != 0)){
		n1 = rand()% nurseTotal;
		//n2 = rand()% nurseTotal;
	}

	swap2shifts(&sol[n1][d], &sol[n2][d]);

}


void diffNurseSwap(char sol[NURSE_NUM][DAY_NUM]){

	int randIdx[28];
	randomDayGen(randIdx, 28);

	int n1 = randIntInterval(0,7);
	int n2 = randIntInterval(8,9);

	int width = randIntInterval(2,9);
	for( int i = 0; i<width; i++){
		swap2shifts(&sol[n1][randIdx[i]], &sol[n2][randIdx[i]]);
	}
}


void diffNurseSlotSwap(char sol[NURSE_NUM][DAY_NUM]){

	int widthStart =14;
	int widthEnd = 27;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

	int n1 = randIntInterval(0,7);
	int n2 = randIntInterval(8,9);

	for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++)
		swap2shifts(&sol[n1][dayIdx],&sol[n2][dayIdx]);
}



void singleNurseMultiDayMove(char sol[NURSE_NUM][DAY_NUM]){

	int randIdx[8];
	randomDayGen(randIdx, 8);

	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;


	for( int i = 0; i < 4; i++){
		
		while ( (n1 == n2) || (sol[n1][randIdx[i]] == 0)&&(sol[n2][randIdx[i]] == 0) || 
			(sol[n1][randIdx[i]] != 0)&&(sol[n2][randIdx[i]] != 0)){
			n2 = rand()% nurseTotal;
		}
		swap2shifts(&sol[n1][randIdx[i]], &sol[n2][randIdx[i]]);
	}
}


// multi day swap 
void nurseSlotSwap(char sol[NURSE_NUM][DAY_NUM]){

	int widthStart = 12;
	int widthEnd = 27;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

  	int n1 = rand()% nurseTotal;
  	int n2 = rand()% nurseTotal;
  	while ( n1 == n2 )
  		n2 = rand()% nurseTotal;

	for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++)
		swap2shifts(&sol[n1][dayIdx],&sol[n2][dayIdx]);
}


void nurseSlotSwap_mid(char sol[NURSE_NUM][DAY_NUM], int widthStart, int widthEnd, int interval1,int interval2 ){

// 	int widthStart = 20;
// 	int widthEnd = 27;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

	//int s = (rand() % (5 - 1 + 1)) + 1; // [1,5]
	int s = randIntInterval(interval1,interval2);

	//int x1 = (rand() % ( (10-2*s) - 0 +1)) + 0;
	int x1 = randIntInterval( 0, 30 - 2*s  );
	int x2 = x1 + s -1;

	//int y1 = (rand() % ( (10-s) - (x2+1) +1)) + (x2+1);
	int y1 = randIntInterval( x2+1, 30-s);

	//printf("%d %d %d\n", s, x1, y1);

	for( int stepIdx = 0; stepIdx < s; stepIdx++){
		for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++){
			swap2shifts(&sol[x1+stepIdx][dayIdx],&sol[y1+stepIdx][dayIdx]);
		}
	}
}





void nurseSlotSwap2(char sol[NURSE_NUM][DAY_NUM]){

	int widthStart = 12;
	int widthEnd = 21;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;
	while ( n1 == n2 )
		n2 = rand()% nurseTotal;

	for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++)
		swap2shifts(&sol[n1][dayIdx],&sol[n2][dayIdx]);


}

void nurseSlotSwap_short(char sol[NURSE_NUM][DAY_NUM]){

	int widthStart =2;
	int widthEnd = 11;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;
	while (n1 == n2)
		n2 = rand()% nurseTotal;

	//static int moveTime = 0;
	//static int a[10] = {0};
	//if( moveTime%5 == 0)randomNurseGen(a,10);
	//int n1 = a[(moveTime*2)%10];
	//int n2 = a[((moveTime*2)%10) + 1];
	//moveTime++;

	for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++)
		swap2shifts(&sol[n1][dayIdx],&sol[n2][dayIdx]);

	

}


void nurseSlotSwap_blk(char sol[NURSE_NUM][DAY_NUM]){

	int widthStart =2;
	int widthEnd = 15;
	int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);


 	int s = (rand() % (5 - 1 + 1)) + 1; // [1,5]
 	int x1 = (rand() % ( (10-2*s) - 0 +1)) + 0;
 	int x2 = x1 + s -1;
 
 	int y1 = (rand() % ( (10-s) - (x2+1) +1)) + (x2+1);
 	int y2 = y1 + s -1;

	for( int stepIdx = 0; stepIdx < s; stepIdx++){

		for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++){
			swap2shifts(&sol[x1+stepIdx][dayIdx],&sol[y1+stepIdx][dayIdx]);
		}
	}


	
}

// wkd swap. Not that effective yet
void nurseWkdSwap(char sol[NURSE_NUM][DAY_NUM]){

	int n1 = rand()% nurseTotal;
	int n2 = rand()% nurseTotal;
	while (n1 == n2)
		n2 = rand()% nurseTotal;


	for(int i = (7-startTimeOffset-1) ; i < DAY_NUM; i+=7){	

		int rand_tmp = rand ()% 10;
		if ( rand_tmp > 4){
			
			int rand_tmp_2 = rand()%10;

			if ( rand_tmp_2 > 4){
				swap2shifts(&sol[n1][i],&sol[n2][i]);
			}
			else{
				swap2shifts(&sol[n1][i+1],&sol[n2][i+1]);
			}

		}
	

	}

// 	char temp;
// 	for(int dayIdx = 0; dayIdx <= 3; dayIdx++){
// 	
// 		temp = sol[n1][dayIdx*7 + 1];
// 		sol[n1][dayIdx*7 + 1] = sol[n2][dayIdx*7 + 1];
// 		sol[n2][dayIdx*7 + 1] = temp;
// 
// 		temp = sol[n1][dayIdx*7 + 2];
// 		sol[n1][dayIdx*7 + 2] = sol[n2][dayIdx*7 + 2];
// 		sol[n2][dayIdx*7 + 2] = temp;
// 	}
}




void cycleMove(char sol[NURSE_NUM][DAY_NUM]){
 	
	int stepLengh = (rand() % (3-1+1)) + 1;
 	//int randDayIdx = rand()% DAY_NUM;
 	
	
	int randIdx[28];
	randomDayGen(randIdx, 28);
	
	int daywidth = (rand() % (25-2+1)) + 2;
	//daywidth = 1;
	
	for(int dayIdx = 0; dayIdx < daywidth; dayIdx++){
		
		int tempDayArray[NURSE_NUM] = {0};

		for( int nurseIdx = 0; nurseIdx < nurseTotal; nurseIdx++)
			tempDayArray[ (nurseIdx + stepLengh) % nurseTotal] = sol[nurseIdx][randIdx[dayIdx]];

		for( int nurseIdx = 0; nurseIdx < nurseTotal; nurseIdx++)
			sol[nurseIdx][randIdx[dayIdx]] = tempDayArray[nurseIdx];

	}
}


void shakingSingleNurse(char sol[NURSE_NUM][DAY_NUM], int nIdx){


	int randIdx[28];
	randomDayGen(randIdx, 28);

	int width = randIntInterval(5,15);


	for( int i = 0; i < width; i++){
		
		int n1 = rand()% nurseTotal;
		while (n1 == nIdx)
			n1 = rand()% nurseTotal;
		swap2shifts(&sol[nIdx][randIdx[i]],&sol[n1][randIdx[i]]);

	}



	//int widthStart = 2;
	//int widthEnd = 6;
	//int dayWidth = (rand()% ( widthEnd - widthStart + 1) ) + widthStart;
	//int startDayIdx = rand()% (DAY_NUM - dayWidth + 1);

	//int n1 = rand()% nurseTotal;
	//while (n1 == nIdx)
	//	n1 = rand()% nurseTotal;

	//for(int dayIdx = startDayIdx; dayIdx <= dayWidth; dayIdx++)
	//	swap2shifts(&sol[n1][dayIdx],&sol[nIdx][dayIdx]);
	
}

void twoNurseShaking(char sol[NURSE_NUM][DAY_NUM]){
	
	//int n1 = rand()% nurseTotal;
	//int n2 = rand()% nurseTotal;
	//while (n1 == n2)
	//	n2 = rand()% nurseTotal;

	//int n3 = rand()% nurseTotal;
	//int n4 = rand()% nurseTotal;


	int a[5];
	randomNurseGen(a,5);


	shakingSingleNurse(sol, a[0]);
	shakingSingleNurse(sol, a[1]);
	//shakingSingleNurse(sol, a[2]);
	//shakingSingleNurse(sol, a[3]);
	//shakingSingleNurse(sol, a[4]);
	//shakingSingleNurse(sol, a[5]);

}





//  the major force of the search
void findNeigh(char sol[NURSE_NUM][DAY_NUM]){
	static int run_time = 0;

// 	if( run_time % 500 == 0 ){
// 		//nurseSlotSwap_blk(sol);
// 		twoNurseShaking(sol);
// 
// 	}
	
	int thehold = rand()% 100;
 	
	if(thehold >40){
		if( thehold > 60 ){
			nurseSlotSwap(sol);

		}
		else {
			//nurseSlotSwap(sol);
			nurseSlotSwap_short(sol);
			//twoNurseMultiDaySwap(sol,5);

			typeIdx = 1;
		}
  	}
   	else{
		if(thehold >20){
			twoNurseMultiDaySwap(sol,2);
			//nurseWkdSwap(sol);
			typeIdx = 2;
		}
		else {
			singleWorkingDayMove(sol);
			//diffNurseSwap(sol);

			typeIdx = 3;
		}
	/*	else {
			nurseSlotSwap_blk(sol);
		}*/
	}

	run_time++;

}


void findNeigh_mid(char sol[NURSE_NUM][DAY_NUM]){
	static int run_time = 0;

	// 	if( run_time % 500 == 0 ){
	// 		//nurseSlotSwap_blk(sol);
	// 		twoNurseShaking(sol);
	// 
	// 	}

	int thehold = rand()% 100;

	if(thehold > 50){
		if( thehold > 70 ){
			if( thehold > 90)	
				nurseSlotSwap_mid(sol,20,27,2,9);
			else 
				nurseSlotSwap_mid(sol,12,21,2,9);
		}
		else {
			nurseSlotSwap_mid(sol,3,9,1,9);

			typeIdx = 1;
		}
	}
	else{
		if(thehold > 5){
			twoNurseMultiDaySwap(sol,2);
			typeIdx = 2;
		}
		else {
			singleWorkingDayMove(sol);
			typeIdx = 3;
		}
		/*	else {
		nurseSlotSwap_blk(sol);
		}*/
	}

	run_time++;

}

void findNeigh_test1(char sol[NURSE_NUM][DAY_NUM]){

	static int run_time = 0;


  	if( run_time % 2 == 1){
  		twoNurseMultiDaySwap(sol,2);
  	}
  	else if( run_time %3 == 1){
 		nurseSlotSwap(sol);
  	}
  	else if( run_time % 5 == 1){
 		nurseSlotSwap_short(sol);
 	}
 	else if( run_time % 7 == 1){
 		singleWorkingDayMove(sol);
 	}


	
 

	run_time++;
}



void findNeigh_intelligent( char sol[NURSE_NUM][DAY_NUM] ){


	char sol_temp[4][NURSE_NUM][DAY_NUM];

	int r[4] = {0};

	solCopy(sol_temp[0], sol);
	twoNurseMultiDaySwap(sol_temp[0],2);
	r[0] = evaluate(sol_temp[0]);

	solCopy(sol_temp[1], sol);
	nurseSlotSwap_short(sol_temp[1]);
	r[1] = evaluate(sol_temp[1]);

	solCopy(sol_temp[2], sol);
	nurseSlotSwap(sol_temp[2]);
	r[2] = evaluate(sol_temp[2]);

	solCopy(sol_temp[3], sol);
	singleWorkingDayMove(sol_temp[3]);
	r[3] = evaluate(sol_temp[3]);

	//printf("\n the 4 are: %d %d %d %d \n", r[0], r[1], r[2], r[3]);
	
	int min = 1000000;
	int min_idx = 0;
	
	
	if( r[0] == r[1] && r[1] == r[2] && r[2] == r[3]){
		min_idx = randIntInterval(0,3);
	}
	else{
		for( int i = 0 ; i < 4; i++){
			if( r[i] < min){
				min = r[i];
				min_idx = i;
			}
		}
	}

	//printf("idx is %d \n", min_idx);

	solCopy(sol, sol_temp[min_idx]);

}


int distanceShift(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]){
	int sum = 0;
	for(int i = 0; i < nurseTotal; i++){
		for(int j = 0; j < DAY_NUM; j++){
			if( a[i][j] != b[i][j] ){
				sum++;
			}
		}
	}
	return sum;
}

int distanceWorkingDay(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]){
	int sum = 0;
	for(int i = 0; i < nurseTotal; i++){
		for(int j = 0; j < DAY_NUM; j++){
			if( a[i][j] != 0 && b[i][j] != 0){
				if( a[i][j] != b[i][j] ){
					sum++;
				}
			}
		}
	}
	return sum;
}




void partDayCopy(char a[NURSE_NUM][DAY_NUM],
				 char b[NURSE_NUM][DAY_NUM],int startDay, int endDay){
	 assert(startDay <= endDay);
	 assert(startDay >=0 && endDay <= DAY_NUM);

	 for(int i = 0; i < NURSE_NUM; i++){
		 for(int j = startDay; j<endDay; j++){
			 a[i][j] = b[i][j];
		 }
	 }
}


void copyDecomp(char a[NURSE_NUM][DAY_NUM], char b[NURSE_NUM][DAY_NUM], char s[NURSE_NUM][DAY_NUM]){

	const int dayNum = 27;

	int randIdx[dayNum];
	randomDayGen(randIdx, dayNum);

	for(int dayIdx = 0; dayIdx < dayNum; dayIdx++){
		for(int nIdx = 0; nIdx < nurseTotal; nIdx++){
			a[nIdx][randIdx[dayIdx]] = s[nIdx][randIdx[dayIdx]];
		}
	}

	randomDayGen(randIdx, dayNum);

	for(int dayIdx = 0; dayIdx < dayNum; dayIdx++){
		for(int nIdx = 0; nIdx < nurseTotal; nIdx++){
			b[nIdx][randIdx[dayIdx]] = s[nIdx][randIdx[dayIdx]];
		}
	}


}


void initShake(char a[NURSE_NUM][DAY_NUM],char s[NURSE_NUM][DAY_NUM]){

	const int dayNum = 2;

	int randIdx[dayNum];
	randomDayGen(randIdx, dayNum);

	for(int dayIdx = 0; dayIdx < dayNum; dayIdx++){
		for(int nIdx = 0; nIdx < nurseTotal; nIdx++){
			a[nIdx][randIdx[dayIdx]] = s[nIdx][randIdx[dayIdx]];
		}
	}

}





// =========================  solution support =========================

void initMole(struct Molecule *a){

	solutionCreate(a->mole);
	//printf("the fitness is  %d \n",evaluate(MoleculePop[i].mole));

	a->PE = evaluate(a->mole);
	solCopy(a->MinStruct, a->mole);

	a->KE = initialKE;
	a->NumHit = 0;
	a->MinPe = a->PE;
	a->MinHit = 0;

	//showMole(a);

}


void resetEnergy(struct Molecule *a){

	a->KE = initialKE;

	//showMole(a);

}


void computInfo(struct Molecule *a){

	a->PE = evaluate(a->mole);
	solCopy(a->MinStruct, a->mole);
	a->KE = initialKE;
	a->NumHit = 0;
	a->MinPe = a->PE;
	a->MinHit = 0;
	//showMole(a);
}


// find the optimal value
int findMinEp( struct Molecule pop[popSizeMax] ){
	int fitMin = 100000;
	int optiIdx = 0;
	for(int i = 0; i < currentPopSize; i++){
		//if (MoleculePop[i].MinPe < fitMin ){
		if ( pop[i].MinPe < fitMin ){
			//fitMin = MoleculePop[i].MinPe;
			fitMin = pop[i].MinPe;
			optiIdx = i;
		}
	}
	return fitMin;
} 


// find the optimal index
int findMinIdx( struct Molecule pop[popSizeMax] ){

	int fitMin = 100000;
	int optiIdx = 0;
	for(int i = 0; i < currentPopSize; i++){
		//if (MoleculePop[i].MinPe < fitMin ){
		if ( pop[i].MinPe < fitMin ){
		//	fitMin = MoleculePop[i].MinPe;
			fitMin = pop[i].MinPe;
			optiIdx = i;
		}
	}
	return optiIdx;
} 


//void watchingCro(){
//	int watTimes = 1;
//	for(int i = 0; i<watTimes; i++){
//		crosearch();
//		solCopy(optiHolder[i],optiSolution);
//		//printf("opti is %d\n", evaluate(optiSolution));
//	}
//	for(int i = 0; i<watTimes; i++){
//		printf("distance is %d\n", hDistance(optiHolder[0],optiHolder[i]));
//	}
//}




void solutionSwap(char sol[NURSE_NUM][DAY_NUM], int dayIdx, int nurse1, int nurse2){

	swap2shifts( &sol[nurse1][dayIdx], &sol[nurse2][dayIdx]);
}


