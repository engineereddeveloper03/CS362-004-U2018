/* ----------------------------------------------------------------------
 * Program Name: randomtestcard1.c
 * Author: Phillip Sturtevant
 * Date: August 12, 2018
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

void checkSmithyCard(int p, int handPos, struct gameState *post)
{
   struct gameState pre;
   memcpy (&pre, post, sizeof(struct gameState));

   int result = smithyEffect(p, post, handPos);

   // manually add 3 cards to the hand
   if (pre.deckCount[p] >= 3) {
      pre.handCount[p] += 3;
      for(int i = 1; i <= 3; i++)
      {
         pre.hand[p][pre.handCount[p]-i] = pre.deck[p][pre.deckCount[p]-1];
         pre.deckCount[p]--;
      }
      // add Smithy card to discard and remove from hand
      pre.discardCount[p]++;
      pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] -1];
      pre.handCount[p]--;
   }
   // shuffle discard and manually give three cards to hand 
   else if (pre.discardCount[p] > 0) {
      memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
      memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
      for(int i = 1; i <= 3; i++)
      {
         pre.hand[p][pre.handCount[p]-i] = pre.deck[p][pre.deckCount[p]-1];
         pre.deckCount[p]--;
      }
      pre.handCount[p] += 3;
      pre.discardCount[p] = 0;
      
      // add Smithy card to discard and remove from hand
      pre.discardCount[p]++;
      pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] -1];
      pre.handCount[p]--;
   }

   // check if number of cards are correct
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0)
   {
      printf("TEST FAILED\n");
      printf("Hand Count: Expected: %d  Result: %d\n", pre.handCount[p], post->handCount[p]);
      printf("Deck Count: Expected: %d  Result: %d\n", pre.deckCount[p], post->deckCount[p]);
      printf("Discard Count: Expected: %d  Result: %d\n", pre.discardCount[p], post->discardCount[p]);
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

   printf("TESTING Smithy card:\nRandom Tests:\n");

   for (n = 0; n < 2000; n++) {
      for (i = 0; i < sizeof(struct gameState); i++) {
         ((char*)&G)[i] = floor(Random() * 256);
      }
      // drawCard setttings
      p = floor(Random() * 2);
      G.deckCount[p] = floor(Random() * MAX_DECK);
      G.discardCount[p] = floor(Random() * MAX_DECK);
      G.handCount[p] = floor(Random() * MAX_HAND);

      // discardCard settings
      handPos = floor(Random() * G.handCount[p]);
      G.whoseTurn = p;
      for (k = 0; k < G.handCount[p]; k++) {
         G.hand[p][k] = floor(Random() * treasure_map);
      }
      for (k = 0; k < G.deckCount[p]; k++) {
         G.deck[p][k] = floor(Random() * treasure_map);
      }
      for (k = 0; k < G.discardCount[p]; k++) {
         G.discard[p][k] = floor(Random() * treasure_map);
      }
      G.playedCardCount = floor(Random() * MAX_DECK);
      for (k = 0; k < G.playedCardCount; k++) {
         G.playedCards[G.playedCardCount] = floor(Random() * treasure_map);
      }

      checkSmithyCard(p, handPos, &G);
   }

   printf("End of random tests.\n\n");

   return 0;
}

