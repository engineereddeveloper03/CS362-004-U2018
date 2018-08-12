/* ----------------------------------------------------------------------
 * Program Name: unittest1.c
 * Author: Phillip Sturtevant
 * Date: August 12, 2018
 * Description: A unit test for the gainCard function in Dominion.
 * ----------------------------------------------------------------------
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"

int main() {
   int i;
   int seed = 1000;
   int numPlayers = 2;
   struct gameState G, testG;
   int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
   
   int supplyPos;
   int toFlag = 0;
   int maxFlag = 2;
   int player = 0;
   int result;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   printf("TESTING gainCard function:\n");


   // Test pulling card from supply not in game "minion" card
   printf("Check if pulling from non-existent Supply\n");
   supplyPos = 17;
   result = gainCard(supplyPos, &G, toFlag, player);

   if (result == -1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Return Expected: -1  Result: %d\n", result);

   // Test pulling card when empty
   supplyPos = 7;
   printf("\nCheck if trying to pull card from empty Supply\n");
   G.supplyCount[supplyPos] = 0; // set supply to 0

   // try to grab card from locatoin
   result = gainCard(supplyPos, &G, toFlag, player);

   if (result == -1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Return Expected: -1  Result: %d\n", result);

   G.supplyCount[supplyPos] = 10; // reset supply

   // Test to see if supply properly reduced & card is only in discard pile
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state
   result = gainCard(supplyPos, &G, toFlag, player);

   int supplyCnt = G.supplyCount[supplyPos];

   if (supplyCnt == 9) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected: %d  Result: %d\n", (testG.supplyCount[supplyPos] - 1), supplyCnt);

   // see if card added only to hand/deck/discard pile depending on flag
   printf("\nCheck if card only added to hand/deck/discard depending on flag set.\n");
   for (i = 0; i <= maxFlag; i++)
   {
      if (i == 0) { printf("Adding to discard...\n"); }
      else if (i == 1) { printf("Adding to deck...\n"); }
      else {printf("Adding to hand...\n"); }
      memset(&G, 23, sizeof(struct gameState));   // clear the game state
      initializeGame(numPlayers, k, seed, &G); // initialize a new game
      memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

      gainCard(supplyPos, &G, i, player);

      int deckPre1 = testG.deckCount[player]; 
      int deckPre2 = testG.deckCount[1];
      int handPre1 = testG.handCount[player];
      int handPre2 = testG.handCount[1];
      int discardPre1 = testG.discardCount[player];
      int discardPre2 = testG.discardCount[1];

      int deckPost1 = G.deckCount[player];
      int deckPost2 = G.deckCount[1];
      int handPost1 = G.handCount[player];
      int handPost2 = G.handCount[1];
      int discardPost1 = G.discardCount[player]; 
      int discardPost2 = G.discardCount[1];

      // discard check
      if (i == 0)
      {
         if((discardPre1 + 1) == discardPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Discard Expected: %d  Result: %d\n", (discardPre1 + 1), discardPost1);
      }
      else
      {
         if(discardPre1 == discardPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Discard Expected: %d  Result: %d\n", discardPre1, discardPost1);
      }
      
      // Player 2 check
      if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
      else { printf("TEST FAILURE\n"); }
      printf("Player 2 Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);
      
      // deck check
      if (i == 1)
      {
         if((deckPre1 + 1) == deckPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Deck Expected: %d  Result: %d\n", (deckPre1 + 1), deckPost1);
      }
      else
      {
         if(deckPre1 == deckPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Deck Expected: %d  Result: %d\n", deckPre1, deckPost1);
      }

      // Player 2 check       
      if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
      else { printf("TEST FAILURE\n"); }
      printf("Player 2 Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

      // hand check
      if (i == 2)
      {
         if((handPre1 + 1) == handPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Hand Expected: %d  Result: %d\n", (handPre1 + 1), handPost1);
      }
      else
      {
         if(handPre1 == handPost1) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Player 1 Hand Expected: %d  Result: %d\n", handPre1, handPost1);
      }

      // Player 2 check
      if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
      else { printf("TEST FAILURE\n"); }
      printf("Player 2 Hand Expected: %d  Result: %d\n", handPre2, handPost2);
   }

   return 0;
}

