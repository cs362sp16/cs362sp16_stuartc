#include "dominion.h"
#include <stdlib.h>
#include <stdio.h>

int fail=0;

void sert(int cond,char *msg){
if(cond == 0){
printf("Assertion FAILED: %s\n",msg);
fail=1;
}
return;
}

//This program is a unit test for "isGameOver"
int main(){
int re=0,i;
struct gameState *fake;
fake=malloc(sizeof(struct gameState));

fake->supplyCount[province]=20;
for(i=0;i<25;i++)
   fake->supplyCount[i]=1;

re=isGameOver(fake);
sert(re==0,"Game shouldn't be over!'");

for(i=5;i<8;i++)   
fake->supplyCount[i]=0;
re=isGameOver(fake);
sert(re==1,"Game should be over due to three supply piles being at zero");

fake->supplyCount[province]=0;
re=isGameOver(fake);
sert(re==1,"Game should be over due to no provinces left");

if(!fail)
   printf("TEST 1 SUCESSFUL COMPLETION\n");

return 0;
}
