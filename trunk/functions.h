
//#ifndef HEADER_H
//#define HEADER_H



// ==================== instance loading =================== 

#define NURSE_NUM 50	// the max number of nurses.max is 50,in long instances.
#define DAY_NUM 28		// period
#define TYPES 5			// shift types, required to increase to 5 later once the head nurse comes in



// different start time of the instances
// For some instances have other start time
extern int startTimeOffset;


extern int nurseTotal;

// nurse skill level
extern int nurseSkill[NURSE_NUM];


// day off request [nurse number][28days] hold the weight
extern int nurseDayoff[NURSE_NUM][DAY_NUM];


//shift off request [nurse num][28 days][shift type;weight]
//extern int nurseShiftoff[NURSE_NUM][DAY_NUM][2];
extern char nurseShiftoff[NURSE_NUM][DAY_NUM][10]; // weight is always 1
extern int nurseShiftoffNum[NURSE_NUM][DAY_NUM];	// one nurse can has multiple request


// because every nurse has her contract, 
// we use this array to map from nurses to contract
// nurse number is NURSE_NUM = 30
extern int nursesContraMap[NURSE_NUM];



// hold instance information
struct InstanceAttributeStruct{
	
	char instanceName[30];
	char instanceStartTime[30];
	
	int skillNum;
	int shiftTypeNum;
	int contractNum;
	int patternNum;
	int nurseNum;
	int weekCoverNum;
	int dayOffReqNum;
	int shiftOffReqNum;
	
	// dayOn, shiftOn, dateSpecific cover 
	// the above three are all zero in
	// each instance
};

extern InstanceAttributeStruct instAttri;



// constraints need to be loaded from the instance
//this is the hard cover, since the 4 weeks are the same
// cover_h[i][j] hold the number of j type needed in weed day i
extern int cover_h[7][5]; 



// hold contract
#define contra struct contract
extern contra{

	// hard constraints, usually leave it alone
	int hardOn1,hardOn2;

	int maxWorkDayOn,maxWorkDayW,maxWorkDay; 
	int minWorkDayOn,minWorkDayW,minWorkDay;

	int maxConWorkDayOn,maxConWorkDayW,maxConWorkDay; 
	int minConWorkDayOn,minConWorkDayW,minConWorkDay;

	int maxConFreeOn,maxConFreeW,maxConFree; 
	int minConFreeOn,minConFreeW,minConFree;

	int maxConWorkWeekendOn,maxConWorkWeekendW,maxConWorkWeekend;
	int minConWorkWeekendOn,minConWorkWeekendW,minConWorkWeekend;

	int maxWorkingWeekendOn,maxWorkingWeekendW,maxWorkingWeekend;

	int wkdDayNum;

	int completeWeekendW,completeWeekendOn;

	int idenShiftInWeekendW,idenShiftInWeekendOn;

	int noNSBfFWeekendW,noNSBfFWeekendOn;

	////////////////////////////////
	// because every skill has a job attribute. for example, L -> nurse, DH->Headnurse
	// thus, if the alter is on, every nurse should work only their job type
	// this cons appears in the long instances
	///////////////////////////////////
	int alternativeW,alternativeOn;   // not considered now

	int unWantPatTotal;

	int unWantPat[20];		// each contract has a list of unwanted pattern ID			

};

// contract array
// number of contract is 5
// since the in the sprint track, max num of contract is 4. I use 5
extern contra contractArray[5];




// hold unwanted patterns
typedef struct uPattern{

	int patIdx;    // no use
	int patWeight;
	int shiftTotal;
	char patSeq[10];

}uPattern;

#define UPATTERNNUMMAX 20

// hold the unwanted pattern ID
extern uPattern unPatArray[UPATTERNNUMMAX];



// check the evaluation method
extern struct penaltyRec pRec;
extern struct penaltyRec nursePenRec[NURSE_NUM];
struct penaltyRec {

	int workingday;
	int consecWorkingday;
	int consecFree;
	int consecWorkingWkd;
	int maxwkd;
	int threeWkd;
	int dayoff;
	int shiftoff;
	int pattern;
	int total;
	int idx;

};


// record the sorted nurse with penalty
extern struct structSortedNurseWithPen sortedNurseWithPen[NURSE_NUM];
struct structSortedNurseWithPen {

	int totalpen;
	int idx;

};

extern int penArray[NURSE_NUM][DAY_NUM];





// ==================== solution ==================
#define popSizeMax 50


// hold the optimal
extern char optiSolution[NURSE_NUM][DAY_NUM];




// ====================== cro search ==================
// CRO global parameters
extern int currentPopSize;
extern double KElossRate;
extern double MoleColl;
extern int initialKE;
extern int al;
extern double be;
extern int buffer;
extern int optiValueGlo;


// for global random number
extern int randomTool;


struct Molecule{
	char mole[NURSE_NUM][DAY_NUM];
	int PE;
	int KE;
	int NumHit;
	int MinPe;
	int MinHit;
	char MinStruct[NURSE_NUM][DAY_NUM];
	int tabulist[NURSE_NUM][DAY_NUM];
}; 















// ====================== functions ==================

void solutionCreate(char s[NURSE_NUM][DAY_NUM]); 


void solutionRosterShowScreen(char s[][DAY_NUM]); // to screen
void solutionShowTofile( char s[][DAY_NUM]); // 2d view to file
void solutionStandardOutputFile( char s[][DAY_NUM]);	// standard view to file



int evaluate(char s[NURSE_NUM][DAY_NUM]);

void Load(char ins_name[]);

void initial();


//float crosearch(int opt_value);
int crosearch();


void experiment();








void onlyNeiSearch();
void tabuTest();
void onlyOnwallSearch();

void watchingCro();

void localSearch(char currentSol[NURSE_NUM][DAY_NUM]);



// ========================= solution =========================
void solutionStandardRead( char s[NURSE_NUM][DAY_NUM], char ins_name[] );


// ========================= operator =========================
void singleShiftSwap(char sol[NURSE_NUM][DAY_NUM]);
void twoNurseMultiDaySwap(char sol[NURSE_NUM][DAY_NUM]);
void singleWorkingDaySwap(char sol[NURSE_NUM][DAY_NUM]);

void nurseSlotSwap2(char sol[NURSE_NUM][DAY_NUM]);

void cycle3nurse(char sol[NURSE_NUM][DAY_NUM]);
void copyDecomp(char a[NURSE_NUM][DAY_NUM], char b[NURSE_NUM][DAY_NUM], char s[NURSE_NUM][DAY_NUM]);
void initShake(char a[NURSE_NUM][DAY_NUM],char s[NURSE_NUM][DAY_NUM]);

void randNurIdx();
int randIntInterval(int start, int end);


void showPop(struct Molecule pop[popSizeMax]);

void randArray(int len);
void randomDayGen(int holdArray[], int len);
void randomNurseGen(int holdArray[], int len);


void solCopy(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]);
void blockSwap(char sol[NURSE_NUM][DAY_NUM]);
void cycleMove(char sol[NURSE_NUM][DAY_NUM]);

void findNeigh(char sol[NURSE_NUM][DAY_NUM]);
void findNeigh_test1(char sol[NURSE_NUM][DAY_NUM]);
void findNeigh_intelligent( char sol[NURSE_NUM][DAY_NUM] );
void findNeigh_mid(char sol[NURSE_NUM][DAY_NUM]);


void multiNurseSingleDaySwap(char sol[NURSE_NUM][DAY_NUM]);
void singleWorkingDayMove(char sol[NURSE_NUM][DAY_NUM]);

void nurseSlotSwap(char sol[NURSE_NUM][DAY_NUM]);
void nurseSlotSwap_mid(char sol[NURSE_NUM][DAY_NUM], int widthStart, int widthEnd, int interval1,int interval2);


void nurseSlotSwap2(char sol[NURSE_NUM][DAY_NUM]);
void shakingSingleNurse(char sol[NURSE_NUM][DAY_NUM], int nIdx);
void twoNurseShaking(char sol[NURSE_NUM][DAY_NUM]);
void twoNurseMultiDaySwap(char sol[NURSE_NUM][DAY_NUM], int dayNum);
void singleNurseMultiDayMove(char sol[NURSE_NUM][DAY_NUM]);
void nurseSlotSwap_blk(char sol[NURSE_NUM][DAY_NUM]);
void swap2shifts( char* a, char* b);

void nurseWkdSwap(char sol[NURSE_NUM][DAY_NUM]);

void diffNurseSwap(char sol[NURSE_NUM][DAY_NUM]);
void diffNurseSlotSwap(char sol[NURSE_NUM][DAY_NUM]);



int cmp( const void *b ,const void *a);

//int hDistance(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]);
int distanceShift(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]);
int distanceWorkingDay(char a[NURSE_NUM][DAY_NUM],char b[NURSE_NUM][DAY_NUM]);



struct historyArrayStruct{
	char sol[NURSE_NUM][DAY_NUM];
};



void initMole(struct Molecule *a);
void resetEnergy(struct Molecule *a);
void computInfo(struct Molecule *a);




int findMinIdx(struct Molecule pop[popSizeMax]);
int findMinEp(struct Molecule pop[popSizeMax]);


void showPenaltySpec();

extern int typeIdx;


extern int lastSwapDay;
extern int lastSwapNurse1;
extern int lastSwapNurse2;


extern int a1;
extern int a2;
extern int a3;


void solutionSwap(char sol[NURSE_NUM][DAY_NUM], int nurseIdx, int day1, int day2);