/* ----------------------------------------------------------------------
 * Program Name: cardtest4.c
 * Author: Phillip Sturtevant
 * Date: July 22, 2018
 * Description: A unit test for the Embargo card in Dominion.
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
		, remodel, smithy, village, baron, great_hall };
   
   int handPos = 5;
   int coinPre = 0;
   int coinPost = 0;
   int choice1 = 5;
   int player = 0;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   // add Embargo card to hand
   G.handCount[player] = 6;
   G.hand[player][handPos] = 22;

   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

   printf("TESTING Embargo card:\n");

   printf("Check if Player received two coins for purchase.\n");

   playEmbargoCard(&G, handPos, choice1);

   coinPre = testG.coins;
   coinPost = G.coins;

   if ((coinPre + 2) == coinPost) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n");  }
   printf("Expected coins: 2  Result: %d\n", (coinPost - coinPre));

   printf("\nCheck if Player 1 trashed card and if all other states are unchanged.\n");

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

   // Check discard piles
   if(discardPre1 == discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Discard Expected: %d  Result: %d\n", discardPre1, discardPost1);
   if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);

   // Check deck cards
   if(deckPre1 == deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Deck Expected: %d  Result: %d\n", deckPre1, deckPost1);
   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   // Check hand cards
   if((handPre1 - 1) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 1 Hand Expected: %d  Result: %d\n", (handPre1 - 1), handPost1);
   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Player 2 Hand Expected: %d  Result: %d\n", handPre2, handPost2);

   printf("\nCheck whether Embargo token was added to card.\n");

   if ((testG.embargoTokens[choice1] + 1) == G.embargoTokens[choice1]) 
   {
      printf("TEST SUCCESS\n");
   }
   else { printf("TEST FAILURE\n");  }
   printf("Embargo Tokens Expected: %d  Result: %d\n", (testG.embargoTokens[choice1] + 1), G.embargoTokens[choice1]);
 
   // Check with kingdom card not being used
   printf("\nCheck if the function exits if the supply does not exist in the game.\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   // add Embargo card to hand
   choice1 = 21;
   G.handCount[player] = 6;
   G.hand[player][handPos] = 22;
 
   int result = playEmbargoCard(&G, handPos, choice1);

   if (result == -1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("State Expected: -1  Result: %d\n", result);

   return 0;
}
