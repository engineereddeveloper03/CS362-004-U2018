/* ----------------------------------------------------------------------
 * Program Name: cardtest1.c
 * Author: Phillip Sturtevant
 * Date: July 22, 2018
 * Description: A unit test for the Smithy card in Dominion.
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
   
   int handPos = 0;
   int player = 0;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

   printf("TESTING Smithy card:\n");

   printf("Check if three cards are given to player\n");

   // adding card to hand
   G.handCount[player] = 6;
   G.hand[player][5] = 13; 

   playSmithyCard(&G, handPos);

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

   // hand check
   if((handPre1 + 3) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Hand Expected: %d  Result: %d\n", (handPre1 + 3), handPost1);

   printf("\nCheck if cards were taken from same player.\n");
 
   // deck check
   if((deckPre1 - 3) == deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Deck Expected: %d  Result: %d\n", (deckPre1 - 3), deckPost1);

   // Player 2 deck check 
   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   printf("\nCheck if the Smithy card was discarded.\n");

   // discard check
   if((discardPre1 + 1) == discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Discard Expected: %d  Result: %d\n", (discardPre1 + 1), discardPost1);

     
   printf("\nCheck the other player's discard pile/hand to make sure they did not get any cards.\n");

   // Player 2 hand check       
   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Hand Expected: %d  Result: %d\n", handPre2, handPost2);
   
   // Player 2 discard pile check
   if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);

   printf("Check states of victory and kingdom card piles are the same.\n");

   for(i = curse; i <= treasure_map; i++)
   {
      // Check Curse Card
      if (i == curse && G.supplyCount[curse] == 10)
      {
         if (G.supplyCount[curse] == 10) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Curse Count Expected: 10  Result: %d\n", G.supplyCount[curse]);
      }
  
      // Check Victory Cards
      if (i > 0 && i <= 3)
      {
         if (G.supplyCount[i] == 8) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Victory Card %d Expected: 8  Result: %d\n", i, G.supplyCount[i]);
      }

      // Check Coin Cards
      int cards;
      if (i > 3 && i <= 6)
      {
         if (i == 4) { cards = 46; }
         else if (i == 5) { cards = 40; }
         else { cards = 30; }
         
         if (G.supplyCount[i] == cards) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Coins Expected: %d  Result: %d\n", cards, G.supplyCount[i]);
      }

      // Check Kingdom Cards
      if (i > 6)
      {
         for (int j = 0; j < 10; j++)
         {
            // set proper card value
            if (k[j] == i)
            {
               if (k[j] == great_hall || k[j] == gardens)
               {
                  cards = 8;
               }
               else { cards = 10; }
               break;
            }
            else { cards = -1; }
         }
         
         // Check values
         if (G.supplyCount[i] == cards) { printf("TEST SUCCESS\n"); }
         else { printf("TEST FAILURE\n"); }
         printf("Kingdom Cards Expected: %d  Result: %d\n", cards, G.supplyCount[i]);
      }
   }

   return 0;
}

