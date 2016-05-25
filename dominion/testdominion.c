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
void sertnum(int cond,char *msg,int one,int two, int three){
   if(cond == 0){
      printf("Assertion FAILED: %s",msg);
      printf(" %d",one);
      printf(" %d",two);
      printf(" %d\n",three);
      fail=1;
   }
   return;
}

int main(int argc, char *argv[]){
   int j,i,re,ranum,match=0,check;
   int players,c1,c2,c3,tout=0;
   int timeout=0;
   struct gameState *test;
   test=malloc(sizeof(struct gameState));
   int cards[10];
   unsigned int seed;

   if(argc<2)
      return -1;

   srand((unsigned int)atoi(argv[1])); //Set seed for rand() to command line input
   seed=((unsigned int)atoi(argv[1])); //setting seed to be passed into initialization
   //Randomly assign 10 cards to play with here
   //
   if(seed<1)
      return -1; //A seed that falls within that logic statement breaks the embedded rng function in dominion

   for(i=0;i<10;i++)
      cards[i]=-1;

   for(i=0;i<10;i++){
      ranum=rand()%(treasure_map+1);
      match=0;
      if( (ranum<adventurer) ){
	// i=i-1;
	ranum=ranum+7;
      }
     // else{
	 for(j=0;j<10;j++){
	    if(ranum==cards[j]){
	       match=1;
	       break;
	    }}
	 if(match==1)
	    i=i-1;
	 else if(match==0)
	    cards[i]=ranum;
	 else
	    return -1;
     // }
   }
   players=rand()%5;
   if(players<2)
      players=players+2;
   else if(players>4)
      return -1;
   
   re=initializeGame(players,cards,seed,test);
   sert(re==0,"Initialization with normal conditions FAILED");
   if(re!=0)
      return -1;
   printf("Game initialized, starting to play\n");
   //Game initialized, ready to play now
   while(!isGameOver(test)){ //Game loop
      for(i=0;i<numHandCards(test);i++){
	 if( handCard(i,test)==copper)
	    test->coins++;	
	 else if(handCard(i,test)==silver)
	    test->coins+=2;
	 else if(handCard(i,test)==gold)
	    test->coins+=3;
      }
      c1=rand()%5;
      c2=rand()%5;
      c3=rand()%5;
      sert(numHandCards(test)>-1, "Number of cards in hand smaller than 0");
      for(i=0;i<numHandCards(test);i++){ //Action
	 if(handCard(i,test)>gold)//Play!	
	    re=playCard(i,c1,c2,c3,test);
	 sertnum(re==0,"playCard failed with choices: ",c1,c2,c3);
      }
      tout=0;
      ranum=rand()%2;
      if(ranum==0){
       while( ((test->numBuys)>0) && (tout<10)){//Buying
	 if((test->numBuys)>1000)
	 return -1; //Infinite loop protection here
	 tout++;
	 check=0;
	 while(check==0){//Pick a card that is in play
	 ranum=rand()%(treasure_map+1);
	 for(i=0;i<10;i++){
	 if(ranum==cards[i])
	 check=1;
	 else if(ranum<adventurer)
	 check=1;
	 }
	 }
	 re=buyCard(ranum,test);
	 sertnum(re==0,"buyCard failed with card choice(first number)= ",ranum,0,0);
	 } }

      timeout++;
      endTurn(test);
      if(timeout>100000){
	 printf("TIMEOUT!\n");
	 return -1;
      }
   }

printf("End scores:\n");
for(i=0;i<players;i++){
   printf("Score for player %d: ",i);
   printf("%d\n",scoreFor(i,test));
}

   return 0;
}
