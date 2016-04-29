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

//This card unit test will be testing "village""
int main(){
   int re;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   int seed=42,hand;
   
   re=initializeGame(2,cards,seed,fake);
   sert(re==0,"Initialization with normal conditions FAILED");
   fake->whoseTurn=1;
   hand=fake->handCount[1];
   fake->hand[1][1]= village;
   re=playCard(1,2,2,2,fake);
   sert(re==0, "Village card FAILED with normal input, choices  shouldn't matter");
   sert((fake->numActions)==2, "Village FAILED to have correct actions");
   sert((fake->handCount[1]) ==hand, "Village FAILED and didn't draw one card");



   if(fail==0)
      printf("CARD TEST 1 PASS\n");

   return 0;
}
