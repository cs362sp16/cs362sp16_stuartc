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
   int j,i,re,ranum,e_count,post;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   int seed=7;
  
   if(argc<2)
      return -1;
  
   srand((unsigned int)atoi(argv[1])); //Set seed to command line input


   for(j=0;j<42000;j++){
   re=initializeGame(2,cards,seed,fake);
   sert(re==0,"Initialization with normal conditions FAILED");
   fake->hand[1][0]=baron;
   fake->whoseTurn=1;
   e_count=0;
   post=0;
   for(i=0;i<5;i++){
   if(fake->hand[1][i]==estate)
      e_count++;
   }
   ranum=rand()%2;//between one and zero (boolean)
   re=playCard(0,ranum,0,0,fake);
   for(i=0;i<5;i++){
   if(fake->hand[1][i]==estate)
      post++;
   }


   if((e_count<=0) && (ranum>0))
      sert(re==-1,"baron FAILED by discarding estate with no estates in original hand");
   else if((e_count!=post)&&(ranum<0))
      sert(re==-1,"baron FAILED, less estates than start without the discard option");
   else if((e_count>0)&&(ranum>0)&&(post>=e_count))
      sert(re==-1,"baron FAILED, discard too many estates");
   else if((ranum>0)&&(post>=e_count)&&(e_count>0))
      sert(re==0,"baron failed with normal discard state");
   else if((ranum<0)&&(post>e_count))
      sert(re==0,"baron failed with normal non-discard");


   }


if(fail==0)
   printf("The BARON could NOT BE BROKEN!\n");

   return 0;
}
