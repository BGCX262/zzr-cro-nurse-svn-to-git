// ====================================================
// The four elementary reaction 
// and the complete process of CRO
//
//
// ====================================================



#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"





int randomTool = (srand(time(NULL)), 0) ;


char  Sol55[NURSE_NUM][DAY_NUM] = {0};


char beforeDecomp[NURSE_NUM][DAY_NUM] = {0};
struct historyArrayStruct historyArray[20] = {0};




clock_t start, finish;
double duration;   



// ========================= the debug =========================
// debug for getchar() in searching
//#define debug_getchar
//#define intell_change




int currentPopSize;		// the inital popSize
double MoleColl;
int initialKE; // the tolerance
double be;
int buffer;
double KElossRate;
int al;
int local_num;
int generation_num;
int optiValueGlo;

char optiSolution[NURSE_NUM][DAY_NUM] = {0};

// 1 for slot
// 2 for move
// 3 for swap
int typeIdx = 0;

int lastSwapDay = 0;
int lastSwapNurse1 = 0;
int lastSwapNurse2 = 0;

int a1 = 90;
int a2 = 60;
int a3 = 30;


// ========================= for record =========================
int onwallNum = 0;
int decompNum = 0; // TODO: from global to inter
int synthNum = 0;
int intcollNum = 0;

char tmpSol1[NURSE_NUM][DAY_NUM] = {0};
char tmpSol2[NURSE_NUM][DAY_NUM] = {0};

int cmp( const void *b ,const void *a){
	return (*(penaltyRec*)a).total > (*(penaltyRec*)b).total ? 1 : -1;
}



void showPenaltySpec(){
	
	printf("\nMaxMinWorkingDay %d, conDay %d, conFree %d, conWkd %d, wkd %d\nthree %d, dayoff %d, shiftoff %d, pat %d\n",
				pRec.workingday,
				pRec.consecWorkingday,
				pRec.consecFree,
				pRec.consecWorkingWkd,
				pRec.maxwkd,
				pRec.threeWkd,
				pRec.dayoff,
				pRec.shiftoff,
				pRec.pattern);
}




void onwall(int idx, struct Molecule pop[popSizeMax] ){

	onwallNum++;
	
	char  newSol[NURSE_NUM][DAY_NUM] = {0};
	
	//solCopy( newSol, MoleculePop[idx].mole);
	solCopy( newSol, pop[idx].mole );
	//solCopy( newSol, MoleculePop[idx].MinStruct);
	

	// main search force
	findNeigh(newSol);
	//findNeigh_mid(newSol);
	//findNeigh_intelligent(newSol);
	//findNeigh_test1(newSol);

	int newPE = evaluate(newSol);

	//printf("%d \n", MoleculePop[idx].PE - newPE );

	//MoleculePop[idx].NumHit++;
	pop[idx].NumHit++;


	if (pop[idx].PE + pop[idx].KE >= newPE){

		// a is between (KElossrate,1)
		double a = KElossRate + ((double)rand()/RAND_MAX)*(1-KElossRate);
		//double a = 0.95;
		
		//printf("loss a is %f ",a);
		// TODO: the tweak of the interval, such as (0.05,0.1) or (0.95,1)?
		// more faster more better, or more slower more better?

		// the newKE should be more and more less		
		//int newKE = (MoleculePop[idx].PE + MoleculePop[idx].KE - newPE)*a;
		int newKE = (pop[idx].PE + pop[idx].KE - newPE)*a;
		
		//buffer += (MoleculePop[idx].PE + MoleculePop[idx].KE - newPE) - newKE; 
		buffer += (pop[idx].PE + pop[idx].KE - newPE) - newKE; 

		//solCopy( MoleculePop[idx].mole, newSol );
		solCopy( pop[idx].mole, newSol );
		//MoleculePop[idx].PE = newPE;
		pop[idx].PE = newPE;
		//MoleculePop[idx].KE = newKE;
		pop[idx].KE = newKE;
		
		if( onwallNum %100 == 0)
			pop[idx].KE += 2;// for test
	

		// update the best
//		if(MoleculePop[idx].PE < MoleculePop[idx].MinPe){
//			MoleculePop[idx].MinPe = MoleculePop[idx].PE;
//			MoleculePop[idx].MinHit =  MoleculePop[idx].NumHit;
//			solCopy(MoleculePop[idx].MinStruct, MoleculePop[idx].mole);
//		}



		if(pop[idx].PE < pop[idx].MinPe){
			pop[idx].MinPe = pop[idx].PE;
			pop[idx].MinHit = pop[idx].NumHit;
			solCopy(pop[idx].MinStruct, pop[idx].mole);
		}

		
		//showMole( MoleculePop[idx] );
		
	}

	

}


void decomp(int idx, struct Molecule pop[popSizeMax]){


	

//  	a1 = (rand() % (100-50+1)) + 50;
//  	a2 = (rand() % (a1-10+1)) + 10;
//  	a3 = (rand() % (a2+1)); 




// 	static int decompIdx = 0;
// 
// 	printf("================\n");
// 	for(int i = 0; i < decompIdx%20; i++ ){
// 		printf("distance is: %d %d\n", distanceShift(pop[findMinIdx(pop)].MinStruct, historyArray[i].sol),
// 			distanceWorkingDay(pop[findMinIdx(pop)].MinStruct, historyArray[i].sol));
// 	}
// 	printf("================\n");
// 
// 	solCopy(historyArray[decompIdx%20].sol,pop[findMinIdx(pop)].MinStruct);
// 	decompIdx++;


// 	printf("distance is: %d %d\n", distanceShift(pop[findMinIdx(pop)].MinStruct, beforeDecomp),
// 		distanceWorkingDay(pop[findMinIdx(pop)].MinStruct, beforeDecomp));
// 	solCopy(beforeDecomp,pop[findMinIdx(pop)].MinStruct);

	//al = 90000; 
	decompNum++;
	

	struct Molecule new1;
	struct Molecule new2;
	struct Molecule new3;


    //solCopy(new1.mole,pop[findMinIdx(pop)].MinStruct);
 	//solCopy(new2.mole,pop[findMinIdx(pop)].MinStruct);
 	//solCopy(new3.mole,pop[findMinIdx(pop)].MinStruct);
	
	solCopy(new1.mole,optiSolution);
	solCopy(new2.mole,optiSolution);
	solCopy(new3.mole,optiSolution);
	


 	//initMole(&new1);
 	//initMole(&new2);

	//copyDecomp(new1.mole, new2.mole, pop[findMinIdx(pop)].MinStruct);


	for(int i = 0; i <1; i++ ){
	//for(int i = 0; i < 20; i++ ){ // medium
  		
		//diffNurseSwap(new1.mole);
		//diffNurseSwap(new2.mole);
		//diffNurseSwap(new3.mole);

 		diffNurseSlotSwap(new1.mole);
 		diffNurseSlotSwap(new2.mole);
 		diffNurseSlotSwap(new3.mole);



		//evaluate(new2.mole);
		//qsort(nursePenRec,NURSE_NUM,sizeof(nursePenRec[0]),cmp);
		//shakingSingleNurse(new2.mole,nursePenRec[0].idx);
	
		//cycleMove(new1.mole);
		//cycleMove(new2.mole);
		//cycleMove(new3.mole);


// 		nurseWkdSwap(new1.mole);
// 		nurseWkdSwap(new2.mole);
// 		nurseWkdSwap(new3.mole);

 	//	char s1[NURSE_NUM][DAY_NUM] = {0};
 	//	solutionCreate(s1);
 	//	initShake(new1.mole,s1);
	
 	//	//nurseSlotSwap_blk(new1.mole);
 	//	nurseSlotSwap_blk(new2.mole);
		//twoNurseShaking(new2.mole);


		//cycleMove(new3.mole);


// 		twoNurseShaking(new1.mole);
		
		//singleNurseMultiDayMove(new1.mole);
		//singleNurseMultiDayMove(new2.mole);
  		//findNeigh(new1.mole);
  		//findNeigh(new2.mole);
  		
  
		//nurseSlotSwap(new1.mole);
		//nurseSlotSwap(new2.mole);

	
 		
  	}




	computInfo(&new1);
	computInfo(&new2);
	computInfo(&new3);

	//printf("new1's value is %d",new1.PE);
	//printf("new2's value is %d",new2.PE);

	

	float Edec;
//	if (MoleculePop[idx].PE + MoleculePop[idx].KE > new1.PE + new2.PE){
	//if ( pop[idx].PE + pop[idx].KE > new1.PE + new2.PE){
	if ( pop[idx].PE * 2 + pop[idx].KE > new1.PE + new2.PE + new3.PE){
		//Edec = MoleculePop[idx].PE + MoleculePop[idx].KE - (new1.PE + new2.PE);
		Edec = pop[idx].PE * 2 + pop[idx].KE - (new1.PE + new2.PE);
		
		goto step13;
	}
	else {
		double delta1 = (double)rand()/RAND_MAX;
		double delta2 = (double)rand()/RAND_MAX;

		delta1 = 1;
		delta2 = 0.99;


		//Edec = pop[idx].PE + pop[idx].KE + 
		//	delta1 * delta2 * buffer - (new1.PE + new2.PE);

		Edec = pop[idx].PE * 2 + pop[idx].KE + 
			delta1 * delta2 * buffer - (new1.PE + new2.PE + new3.PE);
		
		if ( Edec >= 0 ){
		
			buffer = buffer - buffer *delta1 * delta2 ;
step13:
			//double delta3 = (double)rand()/RAND_MAX;
			//double delta3 = 0.5;
			//new1.KE = Edec * delta3;
			//new2.KE = Edec  -  new1.KE;
			
			double delta3 = 0.3;
			double delta4 = 0.3;
			new1.KE = Edec * delta3;
			new2.KE = Edec * delta4;
			new3.KE = Edec  -  new1.KE - new2.KE;
		

			// add to the population
			// copy one new to the selected
			// copy another one to the last
			
			//MoleculePop[currentPopSize] = new2;
			//MoleculePop[idx] = new1;
			
			pop[currentPopSize] = new2;
			pop[currentPopSize+1] = new3;

			pop[idx] = new1;

			currentPopSize+=2;

			//currentPopSize++;

		}
		else {
			pop[idx].NumHit++;
		}
	}
	

}


void synthe(int idx1, int idx2, struct Molecule pop[popSizeMax] ){
	


	//printf("synthe \n");
	assert(idx1 < currentPopSize && idx2 < currentPopSize);

	synthNum++;
	

	// combination of two into one 
	// there should be many method, first, we use two half combine into one

	struct Molecule new1 = {0};

	if( (double)rand()/RAND_MAX > 0.5 ){
	//if( evaluate(pop[idx1].mole) < evaluate(pop[idx2].mole) ){
		solCopy(new1.mole, pop[idx1].mole);
	}
	else
		solCopy(new1.mole, pop[idx2].mole);

	


	// should not use the initialization function but combine the above two
	
	//first half from idx1
// 	for (int i = 0; i < NURSE_NUM ; i++)
// 		for (int j = 0; j < halfpoint ; j++)
// 			//new1.mole[i][j]= MoleculePop[idx1].mole[i][j];
// 			new1.mole[i][j]= pop[idx1].mole[i][j];
// 	
// 	// second half from idx2
// 	for (int i = 0; i < NURSE_NUM ; i++)
// 		for (int j = halfpoint; j < DAY_NUM ; j++)
// 			//new1.mole[i][j]= MoleculePop[idx2].mole[i][j];
// 			new1.mole[i][j]= pop[idx2].mole[i][j];
	


	
	new1.PE = evaluate(new1.mole);
	solCopy(new1.MinStruct, new1.mole);
	new1.NumHit = 0;
	new1.MinPe = new1.PE;
	new1.MinHit = 0;

	//left KE 
	//if(MoleculePop[idx1].PE + MoleculePop[idx2].PE + MoleculePop[idx1].KE + MoleculePop[idx2].KE >=
	if( pop[idx1].PE + pop[idx2].PE + pop[idx1].KE + pop[idx2].KE >=
	new1.PE){
		//new1.KE = MoleculePop[idx1].PE + MoleculePop[idx2].PE + MoleculePop[idx1].KE + 
		new1.KE = pop[idx1].PE + pop[idx2].PE + pop[idx1].KE + 
		//	MoleculePop[idx2].KE - new1.PE;
			pop[idx2].KE - new1.PE;

		// add the two new into the population
		int smallerIdx = (idx1 < idx2 )?idx1:idx2;
		//MoleculePop[smallerIdx] = new1;
		pop[smallerIdx] = new1;
		
		int biggerIdx = (idx1 > idx2 )?idx1:idx2;

		//MoleculePop[biggerIdx] = MoleculePop[currentPopSize-1];
		pop[biggerIdx] = pop[currentPopSize-1];
		
		//memset( &MoleculePop[currentPopSize-1], 0, sizeof(Molecule) );
		memset( &pop[currentPopSize-1], 0, sizeof(Molecule) );
		
		currentPopSize--;
		//printf("pop minus\n");
	}
	else{	// leave alone
		//MoleculePop[idx1].NumHit++;
		pop[idx1].NumHit++;
		//MoleculePop[idx2].NumHit++;
		pop[idx2].NumHit++;
	}

	////showMole(a);
	// TODO test this function

	
}


void intcolli(int idx1,int idx2, struct Molecule pop[popSizeMax]){


	intcollNum++;
		
	char  newSol1[NURSE_NUM][DAY_NUM] = {0};
	char  newSol2[NURSE_NUM][DAY_NUM] = {0};
	
	solCopy( newSol1, pop[idx1].mole);
	solCopy( newSol2, pop[idx2].mole);
	
	
// 	int halfpoint = rand()%(DAY_NUM -2 -1+1) + 1;
// 
// 	for( int dayIdx = 0; dayIdx < halfpoint; dayIdx++){
// 		for(int nIdx = 0; nIdx < nurseTotal; nIdx++){
// 			swap2shifts(&newSol1[nIdx][dayIdx], &newSol2[nIdx][dayIdx]);
// 		}
// 	}
// 	
// 	findNeigh(newSol1);
// 	findNeigh(newSol2);
	//findNeigh_intelligent(newSol1);
	//findNeigh_intelligent(newSol2);
	
	int randIdx[15];
	randomDayGen(randIdx, 15);

	for( int i = 0; i < 15; i++){
		for(int nIdx = 0; nIdx < nurseTotal; nIdx++){
			swap2shifts(&newSol1[nIdx][randIdx[i]], &newSol2[nIdx][randIdx[i]]);
		}
	}



	int newPE1 = evaluate(newSol1);
	pop[idx1].NumHit++;

	int newPE2 = evaluate(newSol2);
	pop[idx2].NumHit++;


//	int Einter = (MoleculePop[idx1].PE + MoleculePop[idx2].PE
//		+ MoleculePop[idx1].KE + MoleculePop[idx2].KE)-( newPE1 + newPE2);

	int Einter = ( pop[idx1].PE + pop[idx2].PE
		+ pop[idx1].KE + pop[idx2].KE)-( newPE1 + newPE2);


	if( Einter >= 0 ){
		
		//printf(" adding \n");
		double a = (double)rand()/RAND_MAX;

		pop[idx1].KE = Einter * a;			
		pop[idx2].KE = Einter  - pop[idx1].KE;

		solCopy( pop[idx1].mole, newSol1);
		solCopy( pop[idx2].mole, newSol2);

		pop[idx1].PE = newPE1;	
		pop[idx2].PE = newPE2;	

		if( pop[idx1].PE < pop[idx1].MinPe){
			pop[idx1].MinPe = pop[idx1].PE;
			pop[idx1].MinHit =  pop[idx1].NumHit;
			solCopy(pop[idx1].MinStruct, pop[idx1].mole);
		}

		if( pop[idx2].PE < pop[idx2].MinPe){
			pop[idx2].MinPe = pop[idx2].PE;
			pop[idx2].MinHit =  pop[idx2].NumHit;
			solCopy(pop[idx2].MinStruct, pop[idx2].mole);
		}
	}
}




//void crosearch( int opt_value){
//float crosearch( int opt_value){
int crosearch(){

	
	// initialization
	currentPopSize = 1;		
	MoleColl= 0.9;
	initialKE = 1000; // the tolerance
	be = 50;// sprint
	be = 5;
	buffer =500;
	KElossRate = 0.5;
	al = 100000; //sprint
	al = 20000; //sprint
	//al = 10000; //sprint
	//al = 500000; //medium
	
	local_num = 0;
	generation_num = 500000000;
//	generation_num = 1;
	optiValueGlo= 0;

	//static FILE *decomp_fout = fopen("decomp_show.txt", "w+");




	struct Molecule MoleculePop[popSizeMax] = {0}; // create a larger holder
	//char optiHolder[10][NURSE_NUM][DAY_NUM] = {0}; // for h distance
	//optiSolution[NURSE_NUM][DAY_NUM] = {0};



	// ================ initial every mole =================
 	for(int moleidx = 0; moleidx < currentPopSize; moleidx++)	// initalize the small size :10
 	{	initMole(&MoleculePop[moleidx]);
 		//solutionShow(MoleculePop[moleidx].mole);
 		printf("\n");
 	}
		




	memset(optiSolution, 0, sizeof(optiSolution));// reset opti



	// =================== search ===================
	int optiFit = 10000;
	int optiFitForLog = 10000;

	
	start = clock();  
	//for (int generationIndex = 0; generationIndex <0 ; generationIndex++){
	for (int generationIndex = 0; generationIndex < generation_num; generationIndex++){
	//for (int generationIndex = 0; generationIndex < 1; generationIndex++){
		
		
		double b = (double)rand()/RAND_MAX;
		if( b  > MoleColl || currentPopSize == 1){// =================== uni reaction ======================
			int selectedIdx = rand()% (currentPopSize);
					
			if (MoleculePop[selectedIdx].NumHit - MoleculePop[selectedIdx].MinHit > al	){	
 				
				//for(int moleidx = 0; moleidx < currentPopSize; moleidx++)	// initalize the small size :10
				//	resetEnergy(&MoleculePop[moleidx]);
				//solutionShow(MoleculePop[moleidx].mole);
				//printf("\n");
				
				
				//int holder = 1;
				decomp(selectedIdx, MoleculePop);
			
	


			}
 			else
 				onwall(selectedIdx, MoleculePop);
 		} 
		else{//=================== inter reaction ===================
			int selectedIdx1 = rand()% (currentPopSize);
			int selectedIdx2 = rand()% (currentPopSize);
			while ( selectedIdx2 == selectedIdx1 )
				selectedIdx2 = rand()% (currentPopSize);

#ifdef intell_change
			// use this condition to let this reaction as effective as the onwall 
			if(MoleculePop[selectedIdx1].NumHit - MoleculePop[selectedIdx1].MinHit > (al/100) ||
				MoleculePop[selectedIdx2].NumHit - MoleculePop[selectedIdx2].MinHit > (al/100)){
#endif			


#ifndef intell_change
			if(MoleculePop[selectedIdx1].KE <= be && MoleculePop[selectedIdx2].KE <= be){
#endif
			
				//if(MoleculePop[selectedIdx1].KE > be && MoleculePop[selectedIdx2].KE > be){
				//printf("KE are %d %d\n",MoleculePop[selectedIdx1].KE,MoleculePop[selectedIdx2].KE);
				//intcolli(selectedIdx1,selectedIdx2);
				//if(findMinEp() < 65)
					synthe(selectedIdx1,selectedIdx2, MoleculePop);
			}
			else
				intcolli(selectedIdx1,selectedIdx2,MoleculePop);
		}


		// logging the pop
		//if( findMinEp(MoleculePop) < optiFitForLog || currentPopSize >1){
		////if( findMinEp() < optiFitForLog ){
		//	//printf("what the \n");
		//	//showPop(MoleculePop);
		//	
		//	optiFitForLog = findMinEp(MoleculePop);
		//	if(currentPopSize >1){
		//		optiFitForLog = 10000;
		//	}
		//}


		optiValueGlo = findMinEp(MoleculePop);


		if (  findMinEp(MoleculePop) < optiFit ){
			optiFit =  findMinEp(MoleculePop);
			//printf("min is %d \n", optiFit);
			printf("min is %d buffer is %d wall %d decom %d syn %d int %d\n", optiFit,buffer,
				onwallNum,decompNum,synthNum,intcollNum);
			
			//showPenaltySpec();


			solCopy(optiSolution,MoleculePop[findMinIdx(MoleculePop)].MinStruct);
			solutionStandardOutputFile(optiSolution);

			//finish = clock();
			//duration = (double)(finish - start) / CLOCKS_PER_SEC;    
		
			
			//printf( "  %1.2f sec\n", duration );  


			// for evaluator test
			//if( optiFit == opt_value){
			//	//solutionOutput(optiSolution);
			//	printf("%d \n", evaluate(optiSolution));
			//	solutionRosterShowScreen(optiSolution);
			//	showPenaltySpec();
			//	solutionStandardOutputFile(optiSolution);
			//	
			//	finish = clock();
			//	duration = (double)(finish - start) / CLOCKS_PER_SEC;    
			//	printf( "%f seconds\n", duration );  
			//	
			//	printf("\n%s",instAttri.instanceName);
			//	return duration;
			//	break;
			//}
		}

		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;    
		if ( duration >8.3){
			printf("min is %d \n", optiFit);
			return optiFit;
			//break;
		}

#ifdef debug_getchar
		//if( findMinEp(MoleculePop) < 80 ){
			getchar();
		//}
#endif

 		
	
	} // search of generations

	//fclose(decomp_fout);
	
}






void experiment(){

	char instance_name[200][30] = {	
		"holder", 
		"instance\\sprint01.txt","instance\\sprint02.txt","instance\\sprint03.txt","instance\\sprint04.txt",
		"instance\\sprint05.txt","instance\\sprint06.txt","instance\\sprint07.txt","instance\\sprint08.txt",
		"instance\\sprint09.txt","instance\\sprint10.txt",
		
		"instance\\sprint_late01.txt","instance\\sprint_late02.txt","instance\\sprint_late03.txt",
		"instance\\sprint_late04.txt","instance\\sprint_late05.txt","instance\\sprint_late06.txt",
		"instance\\sprint_late07.txt","instance\\sprint_late08.txt","instance\\sprint_late09.txt",
		"instance\\sprint_late10.txt",
		
		"instance\\sprint_hidden01.txt","instance\\sprint_hidden02.txt","instance\\sprint_hidden03.txt","instance\\sprint_hidden04.txt",
		"instance\\sprint_hidden05.txt",

		"instance\\medium01.txt","instance\\medium02.txt","instance\\medium03.txt","instance\\medium04.txt",
		"instance\\medium05.txt",

		"instance\\medium_late01.txt","instance\\medium_late02.txt","instance\\medium_late03.txt","instance\\medium_late04.txt",
		"instance\\medium_late05.txt",

		"instance\\medium_hidden01.txt","instance\\medium_hidden02.txt","instance\\medium_hidden03.txt","instance\\medium_hidden04.txt",
		"instance\\medium_hidden05.txt",
	};
 
	int opti_array[50] = {	0,
							56,58,51,59,58,54,56,56,55,52,		// sprint	1 ~ 10; difficult: #4,#7,#10 
							37,42,48,73,44,42,42,17,17,43,		// sprint late	11 ~ 20; easy:18,19, almost diff
							33,32,62,67,59,						// sprint hidden 21-25: tend to trap into the near-optimal
							240,240,236,237,303,	// medium 26 ~ 30
							158,18,29,35,107,		// medium late	31 ~ 35
							130,221,36,80,122,		// medium hidden	36 ~ 40
	};


	//float time_found = 0;


 	// single test
	int sprint_id = 13;
	Load(instance_name[sprint_id]);
	printf("value is %d", crosearch());
	getchar();



	//FILE *file_result = fopen("test_result.txt", "w+");

	//for (int instance_id = 1; instance_id <= 25; instance_id++){
	//	int run_num = 5;
	//	int max_value = 0;
	//	int min_value = 1000;
	//	float total_value = 0;
	//	//float avg_value = 0;

	//	Load(instance_name[instance_id]);

	//	for(int i = 0; i < run_num; i++){

	//		int t = crosearch();
	//		//printf("value is %d", t);
	//		if( t < min_value) min_value = t;
	//		if( t > max_value) max_value = t;
	//		total_value += t;
	//	}

	//	fprintf(file_result,"%s: opti %d max %d, min %d, avg %1.2f\n",instance_name[instance_id],
	//		opti_array[instance_id],max_value,min_value,total_value/run_num);

	//	//printf("%s: max %d, min %d, avg %1.2f\n",instance_name[instance_id],max_value,
	//	//	min_value,total_value/run_num);
	//}

	//
	//fclose(file_result);
	//getchar();





	
	// bat test
	
 	//int run_num = 20;
  //	float min_time = 100000;
  //	float max_time = 0;
  //	
  //	//FILE *experiment_fout = fopen("experiment.txt", "w");
  //	FILE *experiment_fout = fopen("test_dec_neigh_sp03_nurseShakingdecomp.txt", "w");
  //	
  //	for( int sprint_id = 3 ; sprint_id < 4 ; sprint_id++){
  //		
  //		time_found = 0;
  //		
  //		Load(instance_name[sprint_id]);			
  //
  //		for(int i = 0; i < run_num; i++){
  //			int t = crosearch(opti_array[sprint_id]);
  //			if( t < min_time) min_time = t;
  //			if( t > max_time) max_time = t;
  //			time_found += t;
  //		}
  //		//printf("mean is %f", time_found/time_test);
  //		fprintf(experiment_fout,"inst id is %s, run num is %d, mean time is %3.1f, min is %3.1f, max is %3.1f\n",
  //			instance_name[sprint_id],run_num,time_found/run_num, min_time, max_time);
  //	}
  //	fclose(experiment_fout);






}



