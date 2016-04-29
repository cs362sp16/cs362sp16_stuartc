#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>

int fail=0;

void sert(int cond,char *msg){
if(cond == 0){
printf("Assertion FAILED: %s\n",msg);
fail=1;
}
return;
}

//This unit test will be testing "initalizeGame"
int main(){
struct gameState *fake;
fake=malloc(sizeof(struct gameState));
int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
int cards2[9]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel};
int seed=42,re;

re=initializeGame(2,cards,seed,fake);
sert(re==0,"Initialize DID NOT work with NORMAL options");
cards[9]=2000;
re=initializeGame(2,cards,seed,fake);
sert(re==-1,"Game should FAIL with a bogus card");

cards[9]=smithy;
re=initializeGame(-2,cards,seed,fake);
sert(re==-1,"Didn't FAIL with -2 players");

re=initializeGame(2,cards2,seed,fake);
sert(re==-1,"Didn't FAIL with 9 kingdom cards");

free(fake);

if(fail==0)
printf("unittest2 PASS\n");

return 0;
}
