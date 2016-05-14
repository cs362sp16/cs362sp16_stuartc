#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>
#include "dominion_helpers.h"
int fail=0;

void sert(int cond,char *msg,int num){
   if(cond == 0){
      printf("Assertion FAILED: %s",msg);
      printf("%d\n",num);
      fail=1;
   }
   return;
}

//random tester for the card: mine 
int main(int argc, char *argv[]){
   int j,re,choice1,choice2;
   struct gameState *fake;
   fake=malloc(sizeof(struct gameState));
   int cards[10]= {ambassador,cutpurse,embargo,outpost,sea_hag,feast,gardens,mine,remodel,smithy};
   int seed=7;
  
   if(argc<2)
      return -1;
  

   srand((unsigned int)atoi(argv[1])); //Set seed to command line input

for(j=0;j<1000000;j++){

   re=initializeGame(2,cards,seed,fake);
   sert(re==0,"Initialization with normal conditions FAILED seed= ",seed);
   fake->whoseTurn=1;
   //Set random hand
   /*for(i=0;i<5;i++){
      ranum=rand()%treasure_map;//The following conditional statements check if the random card 
      //is being played this game
      if( (ranum<adventurer)||(ranum==ambassador)||(ranum==cutpurse)||(ranum==embargo)||(ranum==outpost)||(ranum==sea_hag)||(ranum==feast)||(ranum==gardens)||(ranum==mine)||(ranum==remodel)||(ranum==smithy)){
	 fake->hand[1][i]=ranum; 	}
      else
	 i=i-1;
   }*/
   fake->handCount[1]=5;
   choice1=rand()%5;
   choice2=rand()%gold;
   choice2=rand()%(treasure_map+3);
//   if(choice2<copper)
  //    choice2=choice2+3;//making sure choice 2 IS a money card
   re=mine_effect(fake,choice1,choice2,1,5); //always using player one, and with five cards in hand handpos is 5

   if(fake->hand[1][choice1]>gold && fake->hand[1][choice1]<copper) //Not a money chosen
      sert(re==-1,"mine did NOT  catch INVALID input hand choice (it wasn't a money card), CHOICE1= ",choice1);
   else if( (getCost(fake->hand[1][choice1])+3) > getCost(choice2))
      sert(re==-1,"mine did NOT catch INVALID choices (cost diff. too high) CHOICE2= ",choice2);
   else if(choice2>copper)
      sert(re==-1,"mine did NOT catch INVALID choice2 of NON-MONEY card, CHOICE2= ",choice2);
   else
      sert(re==0,"mine card FAILED with normal inputs",choice1);

//  free(fake);
}

   return 0;
}
