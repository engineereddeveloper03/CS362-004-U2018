/* ----------------------------------------------------------------------
 * Program Name: unittest4.c
 * Author: Phillip Sturtevant
 * Date: Autust 12, 2018
 * Description: A unit test for the isGameOver function in Dominion.
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
   struct gameState G;
   int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
   
   int result;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   printf("TESTING isGameOver function:\n");

   printf("Check if the game continues if each pile is still active.\n");

   result = isGameOver(&G);

   if (result == 0) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Result = 0  Result = %d\n", result);

   // set Province to 0 to see if game ends
   printf("\nCheck if the game ends if all province cards are gone.\n");

   G.supplyCount[province] = 0;

   result = isGameOver(&G);

   if (result == 1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Result = 1  Result = %d\n", result);

   printf("\nCheck that if 1 supply card is gone, game still continues.\n");

   // reset game for next test
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   G.supplyCount[adventurer] = 0;
   
   result = isGameOver(&G);

   if (result == 0) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Result = 0  Result = %d\n", result);
   
   printf("\nCheck that if 2 supply cards are gone, game still continues.\n");

   // reset game for next test
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   G.supplyCount[adventurer] = 0;
   G.supplyCount[feast] = 0;

   result = isGameOver(&G);

   if (result == 0) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Result = 0  Result = %d\n", result);

   printf("\nCheck that if 3 supply cards are gone, game ends.\n");

   // reset game for next test
   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game

   G.supplyCount[adventurer] = 0;
   G.supplyCount[feast] = 0;
   G.supplyCount[smithy] = 0;

   result = isGameOver(&G);

   if (result == 1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Result = 1  Result = %d\n", result);

   return 0;
}
