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

//This card unit test will be testing "baron"
int main(){
   int re;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   int seed=42,buys;
   
   re=initializeGame(2,cards,seed,fake);
   sert(re==0,"Initialization with normal conditions FAILED");
   fake->whoseTurn=1;
   fake->hand[1][1]=baron;
   buys=fake->numBuys;
   re=playCard(1,0,0,0,fake);
   sert(re==0,"Playcard FAILED in the first place with baron");

   sert((fake->numBuys) == (buys+1), "baron FAILED by NOT adding one buy exactly");

   

if(fail==0)
   printf("CARD TEST 2 PASS\n");

return 0; 
}
