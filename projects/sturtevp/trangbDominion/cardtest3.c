/* ----------------------------------------------------------------------
 * Program Name: cardtest3.c
 * Author: Phillip Sturtevant
 * Date: August 12, 2018
 * Description: A unit test for the Sea Hag Card in Dominion.
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
   int seed = 1000;
   int numPlayers = 2;
   struct gameState G, testG;
   int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, sea_hag, baron, great_hall };
   
   int player = 0;
   int coin_bonus = 0;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

   printf("TESTING Sea Hag Card:\n");

   cardEffect(25, 0, 0, 0, &G, 0, &coin_bonus);

   printf("Check Player 2's deck to make sure they discarded a card and received curse.\n");

   // Get pre and post deck counts
   int deckPre1 = testG.deckCount[player]; 
   int deckPre2 = testG.deckCount[1];
   int deckPost1 = G.deckCount[player];
   int deckPost2 = G.deckCount[1];

   // Get pre and post hand counts
   int handPre1 = testG.handCount[player];
   int handPre2 = testG.handCount[1];
   int handPost1 = G.handCount[player];
   int handPost2 = G.handCount[1];

   // Get pre and post discard piles
   int discardPre1 = testG.discardCount[player];
   int discardPre2 = testG.discardCount[1];
   int discardPost1 = G.discardCount[player]; 
   int discardPost2 = G.discardCount[1];

   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   printf("\nCheck Player 2 discard pile for added card from deck.\n");

   if((discardPre2 + 1) == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Discard Expected: %d  Result: %d\n", (discardPre2 + 1), discardPost2);

   printf("\nCheck Player 1 deck to ensure it is unchanged.\n");

   if(deckPre1 == deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Deck Expected: %d  Result: %d\n", deckPre1, deckPost1);

   printf("\nCheck Player 1 discard pile and hand for change from dropping Sea Hag Card\n");

   // Check Player's hand and discard for discarded card
   if((discardPre1 + 1) == discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Discard Expected: %d  Result: %d\n", (discardPre1 + 1), discardPost1);

   if((handPre1 - 1) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Hand Expected: %d  Result: %d\n", (handPre1 - 1), handPost1);

   printf("\nCheck Player 2 hand making sure it is unchanged.\n");

   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Hand Expected: %d  Result: %d\n", handPre2, handPost2);

   printf("\nCheck curse cards are removed from the supply pile.\n");

   int cursePre = testG.supplyCount[curse];
   int cursePost = G.supplyCount[curse];

   if((cursePre - 1) == cursePost) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Curses Expected: %d  Result: %d\n", (cursePre - 1), cursePost);

   return 0;
}
