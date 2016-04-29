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

//This unit test will be testing "endTurn"" 
int main(){
   int i,re;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   fake->numPlayers=3;
   fake->whoseTurn=1;
   fake->handCount[1]=3;
   fake->deckCount[1]=5;
   fake->discardCount[1]=0;
   for(i=0;i<3;i++)
      fake->hand[1][i]=4; //coppers
   for(i=0;i<5;i++)
      fake->deck[1][i]=4; //coppers

re=endTurn(fake);
sert(re==0,"endTurn FAILED with normal input");

fake->numPlayers=MAX_PLAYERS+5;
re=endTurn(fake);
sert(re==-1, "endTurn did NOT FAIL with invalid numPlayers");



if(fail==0)
   printf("TEST 4 PASS\n");


return 0;
}


