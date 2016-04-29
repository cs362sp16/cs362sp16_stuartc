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

//This unit test will be testing "scoreFor" 
int main(){
   int i,re;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   //int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   fake->handCount[2]=MAX_HAND;
   fake->deckCount[2]=1;
   fake->discardCount[2]=0;
   for(i=0;i<MAX_HAND;i++)
      fake->hand[2][i]= 1; //Player has a ton of estates
   fake->deck[2][0]=20000;

   re=scoreFor(2,fake);
   sert(re==-9999,"Did NOT fail from invalid card");


   fake->handCount[2]=MAX_HAND;
   fake->deckCount[2]=MAX_DECK;
   fake->discardCount[2]=0;
   for(i=0;i<MAX_HAND;i++)
      fake->hand[2][i]=1; //estates!
   for(i=0;i<MAX_DECK;i++)
      fake->deck[2][i]=1; //estates!
   re=scoreFor(2,fake);
   sert(re>0, "FAIL with full hand and deck of estates");

   re=scoreFor(30000,fake);
   sert(re==-9999,"Did NOT fail with INVALID player");








   if(fail==0)
      printf("TEST3 ALL PASS\n");

   return 0;
}
