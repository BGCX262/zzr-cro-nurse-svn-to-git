// ==================================================
//	read the solution from the website 
//	created by lv zhipeng
// ==================================================


#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include"functions.h"


//FILE *solRead;


void solutionStandardRead( char s[NURSE_NUM][DAY_NUM], char ins_name[] ){

	FILE *solRead;

	errno_t err;
	err =  fopen_s(&solRead,ins_name, "r");


	//err =  fopen_s(&solRead,"sprint_late05_sol.txt", "r");
	//err =  fopen_s(&solRead,"medium_late04_sol.txt", "r");
	//err =  fopen_s(&solRead,"solutions\\long_late01_sol.txt", "r");
	//err =  fopen_s(&solRead,"sprint_hidden10_sol.txt", "r");
	//err =  fopen_s(&solRead,"solutions\\sprint03_sol.txt", "r");
	//err =  fopen_s(&solRead,"solutions\\sprint_late03_sol.txt", "r");
	//err =  fopen_s(&solRead,"solutions\\sprint_late06_sol.txt", "r");
	//err =  fopen_s(&solRead,"solutions\\zzrSolu.txt", "r");
	


	char tmp[500];

// 	while(   fscanf_s(solRead,"%s",tmp, 500) != EOF   ){
// 		puts(tmp);
// 	}
	int assNum = 0;
	for(int i = 0; i<12; i++){
		fscanf_s(solRead,"%s",tmp, 500);
		if( i == 10 ){
			assNum = atoi(tmp);
			//printf("ass num is %d\n", assNum);
		}
	}

	for(int i = 0; i < assNum ; i++){
		//fscanf_s(solRead,"%s",tmp, 500);
		int t1 = 0;
		int t2 = 0;
		int dayIdx = 0;
		fscanf(solRead,"%d-%d-%d,",&t1,&t2,&dayIdx);
		//puts(tmp);
		//printf("%d %d %d ",t1,t2,dayIdx);
			
		
		int nurseIdx;
		fscanf(solRead,"%d,",&nurseIdx);
		//printf("%d \n", nurseIdx);


		char shiftTmp;
		fscanf_s(solRead,"%s",tmp, 500);
		
		if( tmp[0] == 'D' && tmp[1] == 'H'){
			//printf(" H appears \n");
			shiftTmp = 'H';
		}
		else 
			shiftTmp = tmp[0];
		//printf("%c \n", shiftTmp);

		s[nurseIdx][dayIdx-1] = shiftTmp;
		



	}
		
	fclose(solRead);
	//solutionRosterShowScreen(s);

	//printf("the fit I evaluate is %d \n", evaluate(s));

}