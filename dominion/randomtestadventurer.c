#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>
#include "dominion_helpers.h"
int fail=0;

void sert(int cond,char *msg){
   if(cond == 0){
      printf("Assertion FAILED: %s\n",msg);
      fail=1;
   }
   return;
}

//random tester for the card: baron
int main(int argc, char *argv[]){
   int j,i,re,t_count=0,count=0;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   int seed=7;
  
   if(argc<2)
      return -1;
  
   srand((unsigned int)atoi(argv[1])); //Set seed to command line input


   for(j=0;j<420000;j++){
   seed=(rand()%1000)+1;
   re=initializeGame(2,cards,seed,fake);
   sert(re==0,"Initialization with normal conditions FAILED");
   fake->hand[1][0]=adventurer;
   fake->whoseTurn=1;
   t_count=0;
   for(i=0;i<6;i++){
   if( (fake->hand[1][i]>province)&&(fake->hand[1][i]<adventurer) )
      t_count++;
   }

   re=playCard(0,0,0,0,fake);


   count=0;
   for(i=0;i<6;i++){
   if( (fake->hand[1][i]>province)&&(fake->hand[1][i]<adventurer) )
      count++;
   }
   sert(count==(t_count+2),"adventurer FAILED, new treasure count was not TWO more than original before playing card");
   sert(re==0, "adventuerer FAILED with normal conditions");


   }

   return 0;

}
