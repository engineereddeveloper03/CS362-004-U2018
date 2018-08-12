/* ----------------------------------------------------------------------
 * Program Name: cardtest2.c
 * Author: Phillip Sturtevant
 * Date: August 12, 2018
 * Description: A unit test for the Adventurer Card in Dominion.
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

   int player = 0;   
   int drawntreasure = 0;
   int temphand[MAX_HAND];


   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state
 
   // modify original deck (ensure Adventurer card is placing in discard pile)
   G.deck[player][G.deckCount[player] - 1] = 14;
   G.deck[player][G.deckCount[player] - 2] = 4;
   G.deck[player][G.deckCount[player] - 3] = 4;
   G.deck[player][G.deckCount[player] - 4] = 4;

   printf("TESTING Adventurer Card:\n");

   adventurerEffect(drawntreasure, player, &G, temphand);

   printf("Check that the player was given two cards.\n");

   int handPre1 = testG.handCount[player];
   int handPost1 = G.handCount[player];
   
   // Player 2 Check
   int handPre2 = testG.handCount[1];
   int handPost2 = G.handCount[1];
   int deckPre2 = testG.deckCount[1];
   int deckPost2 = G.deckCount[1];
   int discardPre2 = testG.discardCount[1];
   int discardPost2 = G.discardCount[1];


   if((handPre1 + 2) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Hand Expected: %d  Result: %d\n", (handPre1 + 2), handPost1);

   printf("Check that other player's cards did not change.\n");

   // Player 2 check
   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Hand Expected: %d  Result: %d\n", handPre2, handPost2);

   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);

   // Check given cards were treasure cards
   printf("\nCheck that the cards given were treasure cards\n");

   int initTreasure = 0;
   int postTreasure = 0;
   for (i = 0; i < testG.handCount[player]; i++)
   {
      if (testG.hand[player][i] >= 4 && testG.hand[player][i] <= 6)
      {
         initTreasure++;
      }
   }
   for (i = 0; i < G.handCount[player]; i++)
   {
      if (G.hand[player][i] >= 4 && G.hand[player][i] <= 6)
      {
         postTreasure++;
      }
   }

   if ((postTreasure - initTreasure) == 2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n");  }
   printf("Expected treasure: 2  Result: %d\n", (postTreasure - initTreasure));
 
   // Check discard/deck for differences
   printf("\nCheck discard and deck for differences.\n");

   int deckPre1 = testG.deckCount[player]; 
   int discardPre1 = testG.discardCount[player];
   int deckPost1 = G.deckCount[player];
   int discardPost1 = G.discardCount[player];

   if(discardPre1 != discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Beginning Discard: %d  End Discard: %d\n", discardPre1, discardPost1);
   
   if(deckPre1 != deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Beginning Deck: %d  End Deck: %d\n", deckPre1, deckPost1);

   // Check that cards in discard pile are shuffled and placed in deck
   printf("\nCheck the discard pile is shuffled into the deck when looking for treasure.\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game
 
   // set up deck to be empty (to shuffle into)
   G.deckCount[player] = 0;

   // add cards to discard in order
   G.discardCount[player] = 9;
   for (i = 0; i < 9; i++)
   {
      // setup treasure
      if (i % 2 == 0)
      {
         G.discard[player][i] = 4;
      }
      else
      {
         G.discard[player][i] = 7;
      }
   }

   adventurerEffect(drawntreasure, player, &G, temphand);


   // check if deck is the same (confirm shuffle)
   int shuffled = 1;
   for (i = 0; i < 9; i++)
   {
      // setup treasure
      if (i % 2 == 0)
      {
         if (G.discard[player][i] != 4) 
         { 
            shuffled = 0;
         }
      }
   }

   if (shuffled == 0) { printf("TEST SUCCESS - Cards were shuffled.\n"); }
   else { printf("TEST FAILURE - Cards were not shuffled.\n"); }

   return 0;
}
