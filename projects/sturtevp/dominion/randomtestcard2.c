/* ----------------------------------------------------------------------
 * Program Name: randomtestcard2.c
 * Author: Phillip Sturtevant
 * Date: August 5 2018
 * Description: A random tester for the Smithy card in Dominion.
 * ----------------------------------------------------------------------
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "string.h"

void checkSeaHagCard(int p, int handPos, struct gameState *post)
{
   struct gameState pre;
   memcpy (&pre, post, sizeof(struct gameState));

   int result = playSeaHagCard(post);

   // manually remove 1 card from player 1's deck
   if (pre.deckCount[p - 1] > 0) {
      pre.discardCount[p - 1]++;
      pre.discard[p - 1][pre.discardCount[p - 1]] = pre.deck[p - 1][pre.deckCount[p - 1]];
      pre.deck[p - 1][pre.deckCount[p - 1]] = 0; // set curse card on top of deck
      
      // add Sea Hag card to discard and remove from hand who played it
      pre.discardCount[p]++;
      pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] -1];
      pre.handCount[p]--;
   }
   // shuffle discard and manually give three cards to hand 
   else if (pre.discardCount[p] > 0) {
      memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
      memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
      // give curse card after deck shuffle
      pre.discardCount[p - 1]++;
      pre.discard[p - 1][pre.discardCount[p - 1]] = pre.deck[p - 1][pre.deckCount[p - 1]];
      pre.deck[p - 1][pre.deckCount[p - 1]] = 0; // set curse card on top of deck
      
      // add Sea Hag card to discard and remove from hand who played it
      pre.discardCount[p]++;
      pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] -1];
      pre.handCount[p]--;
   }

   // check if number of cards are correct
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0)
   {
      printf("TEST FAILED\n");
      printf("Hand Count 1: Expected: %d  Result: %d\n", pre.handCount[0], post->handCount[0]);
      printf("Deck Count 1: Expected: %d  Result: %d\n", pre.deckCount[0], post->deckCount[0]);
      printf("Discard Count 1: Expected: %d  Result: %d\n", pre.discardCount[0], post->discardCount[0]);
      printf("Hand Count 2: Expected: %d  Result: %d\n", pre.handCount[p], post->handCount[p]);
      printf("Deck Count 2: Expected: %d  Result: %d\n", pre.deckCount[p], post->deckCount[p]);
      printf("Discard Count 2: Expected: %d  Result: %d\n", pre.discardCount[p], post->discardCount[p]);
   }

   // check if return value is 0
   if (result != 0)
   {
      printf("TEST FAILED\n");
      printf("Expected: 0  Result: %d\n", result);
   }
}

int main() {
   int i, n, k, p, handPos;
   struct gameState G;
   
   SelectStream(2);
   PutSeed(3);

   printf("TESTING Sea Hag card:\nRandom Tests:\n");

   for (n = 0; n < 2000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
         ((char*)&G)[i] = floor(Random() * 256);
      }
      
      // setting each player's random hands
      p = 1; // need more than 1 player for card to work properly
      for (int j = 0; j <= p; j++)
      {
         G.deckCount[j] = floor(Random() * MAX_DECK);
         G.discardCount[j] = floor(Random() * MAX_DECK);
         G.handCount[j] = floor(Random() * MAX_HAND);
      }
      
      for (int m = 0; m <= p; m++)
      {
         for (k = 0; k < G.handCount[m]; k++) {
            G.hand[m][k] = floor(Random() * treasure_map);
         }
         for (k = 0; k < G.deckCount[m]; k++) {
            G.deck[m][k] = floor(Random() * treasure_map);
         }
         for (k = 0; k < G.discardCount[m]; k++) {
            G.discard[m][k] = floor(Random() * treasure_map);
         }
      }

      // discardCard settings (not in card implementation, but should be set)
      handPos = floor(Random() * G.handCount[p]);
      G.whoseTurn = p;
      G.playedCardCount = floor(Random() * MAX_DECK);
      for (k = 0; k < G.playedCardCount; k++) {
         G.playedCards[G.playedCardCount] = floor(Random() * treasure_map);
      }

      // Sea Hag settings
      G.numPlayers = p + 1;

      checkSeaHagCard(p, handPos, &G);
   }

   printf("End of random tests.\n\n");

   return 0;
}

