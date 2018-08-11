/* ----------------------------------------------------------------------
 * Program Name: unittest3.c
 * Author: Phillip Sturtevant
 * Date: July 22, 2018
 * Description: A unit test for the scoreFor function in Dominion.
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
   struct gameState G;
   int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
   
   int player = 0;
   int score;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   printf("TESTING scoreFor function:\n");

   printf("Checking proper addition of each card type for the hand.\n");
   // Clearing hand/deck
   for(i = 0; i < 10; i++)
   {
      G.hand[player][i] = -1;
      G.deck[player][i] = -1;
   }
   G.handCount[player] = 6;
   G.deckCount[player] = 0;
   
   // add each card type to hand
   G.hand[player][0] = 0;
   G.hand[player][1] = 1;
   G.hand[player][2] = 2;
   G.hand[player][3] = 3;
   G.hand[player][4] = 16;
   G.hand[player][5] = 10;

   score = scoreFor(player, &G);

   if (score == 10) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n");}
   printf("Score Expected: 10  Result: %d\n", score);

   printf("\nChecking proper addition of garden card.\n");
   G.handCount[player] = 10;
   G.hand[player][6] = 1;
   G.hand[player][7] = 1;
   G.hand[player][8] = 1;
   G.hand[player][9] = 1;

   score = scoreFor(player, &G);

   if (score == 15) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Score Expected: 15  Result: %d\n", score);

   printf("\nChecking proper addition of each card type for the discard pile.\n");

   // reset game and remove cards in hand
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   // Clearing hand/deck
   for(i = 0; i < 10; i++)
   {
      G.hand[player][i] = -1;
      G.deck[player][i] = -1;
   }
   G.handCount[player] = 0;
   G.deckCount[player] = 0;

   // add cards to discard
   G.discardCount[player] = 6;

   G.discard[player][0] = 0;
   G.discard[player][1] = 1;
   G.discard[player][2] = 2;
   G.discard[player][3] = 3;
   G.discard[player][4] = 16;
   G.discard[player][5] = 10;

   score = scoreFor(player, &G);

   if (score == 10) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Score Expected: 10  Result: %d\n", score);

   printf("\nChecking proper addition of each card type for the deck.\n");

   // reset game and remove cards in hand
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   // Clearing hand/deck
   for(i = 0; i < 10; i++)
   {
      G.hand[player][i] = -1;
      G.deck[player][i] = -1;
   }
   G.handCount[player] = 0;
   G.deckCount[player] = 0;

   // add cards to deck
   G.deckCount[player] = 7;

   G.deck[player][0] = 0;
   G.deck[player][1] = 1;
   G.deck[player][2] = 2;
   G.deck[player][3] = 3;
   G.deck[player][4] = 16;
   G.deck[player][5] = 10;

   score = scoreFor(player, &G);

   if (score == 10) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Score Expected: 10  Result: %d\n", score);

   printf("\nChecking proper addition between hand/deck/discard piles.\n");

   // reset game and remove cards in hand
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   // Clearing hand/deck
   for(i = 0; i < 10; i++)
   {
      G.hand[player][i] = -1;
      G.deck[player][i] = -1;
   }
   G.handCount[player] = 1;
   G.hand[player][0] = 1;
   G.deckCount[player] = 1;
   G.deck[player][0] = 1;
   G.discardCount[player] = 1;
   G.discard[player][0] = 1;

   score = scoreFor(player, &G);

   if (score == 3) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Score Expected: 3  Result: %d\n", score);

   printf("\nChecking decks unchanged after addition.\n");

   if(G.handCount[player] == 1 && G.deckCount[player] == 1 && G.discardCount[player] == 1)
   {
      printf("TEST SUCCESS\n");
   }
   else { printf("TEST FAILURE\n"); }
   printf("Hand Count Expected: 1 Result: %d\n", G.handCount[player]);
   printf("Deck Count Expected: 1 Result: %d\n", G.deckCount[player]);
   printf("Discard Count Expected: 1 Result: %d\n", G.discardCount[player]);
   
   return 0;
}
