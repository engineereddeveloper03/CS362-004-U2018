/* ----------------------------------------------------------------------
 * Program Name: unittest2.c
 * Author: Phillip Sturtevant
 * Date: August 12, 2018
 * Description: A unit test for the discardCard function in Dominion.
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
  
   int trashFlag; 
   int handPos = 1;
   int player = 0;

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   printf("TESTING discardCard function:\n");

   trashFlag = 1;

   printf("Checking if card is properly trashed\n");   
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state   
   discardCard(handPos, player, &G, trashFlag);
   
      int deckPre1 = testG.deckCount[player]; 
      int deckPre2 = testG.deckCount[1];
      int handPre1 = testG.handCount[player];
      int handPre2 = testG.handCount[1];
      int discardPre1 = testG.discardCount[player];
      int discardPre2 = testG.discardCount[1];
      int playedPre1 = G.playedCardCount;

      int deckPost1 = G.deckCount[player];
      int deckPost2 = G.deckCount[1];
      int handPost1 = G.handCount[player];
      int handPost2 = G.handCount[1];
      int discardPost1 = G.discardCount[player]; 
      int discardPost2 = G.discardCount[1];
   int playedPost1 = G.playedCardCount;

   printf("Player 1:\n");
   if(discardPre1 == discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Discard Expected: %d  Result: %d\n", discardPre1, discardPost1);

   if(deckPre1 == deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Deck Expected: %d  Result: %d\n", deckPre1, deckPost1);

   if((handPre1 - 1) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Hand Expected: %d  Result: %d\n", (handPre1 - 1), handPost1);

   printf("Player 2:\n");
   if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);

   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Hand Expected: %d  Result: %d\n", handPre2, handPost2);

   if(playedPre1 == playedPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Played Cards Expected: %d  Result: %d\n", playedPre1, playedPost1);

   printf("\nChecking if not trashed, the card is in the played pile.\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state
   trashFlag = 0;

   discardCard(handPos, player, &G, trashFlag);

   deckPre1 = testG.deckCount[player]; 
   handPre1 = testG.handCount[player];
   discardPre1 = testG.discardCount[player];
   playedPre1 = testG.playedCardCount;

   deckPost1 = G.deckCount[player];
   handPost1 = G.handCount[player];
   discardPost1 = G.discardCount[player]; 
   playedPost1 = G.playedCardCount;

   printf("Player 1:\n");
   if(discardPre1 == discardPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Discard Expected: %d  Result: %d\n", discardPre1, discardPost1);

   if(deckPre1 == deckPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Deck Expected: %d  Result: %d\n", deckPre1, deckPost1);

   if((handPre1 - 1) == handPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Hand Expected: %d  Result: %d\n", (handPre1 - 1), handPost1);

   printf("Player 2:\n");
   if(discardPre2 == discardPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Discard Expected: %d  Result: %d\n", discardPre2, discardPost2);

   if(deckPre2 == deckPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Deck Expected: %d  Result: %d\n", deckPre2, deckPost2);

   if(handPre2 == handPost2) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Hand Expected: %d  Result: %d\n", handPre2, handPost2);

   if((playedPre1 + 1) == playedPost1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Played Cards Expected: %d  Result: %d\n", (playedPre1 + 1), playedPost1);

   printf("\nChecking if replaced card is last in hand.\n");

   int lastCard = testG.hand[player][(testG.handCount[player] - 1)];
   
   if (lastCard == G.hand[player][handPos]) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Expected Card: %d  Result: %d\n", lastCard, G.hand[player][handPos]);
   
   printf("\nIf last card in hand, only remove it and don't set other cards.\n");

   memset(&G, 23, sizeof(struct gameState));   // clear the game state
   initializeGame(numPlayers, k, seed, &G); // initialize a new game
   memcpy(&testG, &G, sizeof(struct gameState)); // copy game state

   // remove all cards from hand except 1
   for (i = 1; i < 5; i++)
   {
      G.hand[player][i] = -1;
   }
   G.handCount[player] = 1;
   handPos = 0;

   discardCard(handPos, player, &G, trashFlag);

   int cardInHand = G.hand[player][handPos];
   int totalCards = G.handCount[player];

   if (cardInHand == -1) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Card Enum Expected: -1  Result: %d\n", cardInHand);

   if (totalCards == 0) { printf("TEST SUCCESS\n"); }
   else { printf("TEST FAILURE\n"); }
   printf("Total Cards Expected: 0  Result: %d\n", totalCards);

   return 0;
}
