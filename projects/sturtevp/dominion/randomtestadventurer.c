/* ----------------------------------------------------------------------
 * Program Name: randomtestadventurer.c
 * Author: Phillip Sturtevant
 * Date: August 5 2018
 * Description: A random tester for the Adventurer card in Dominion.
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

void checkAdventurerCard(int p, int handPos, struct gameState *post)
{
   struct gameState pre;
   memcpy (&pre, post, sizeof(struct gameState));

   int result = playAdventurerCard(post);

   // manually look for 2 treasure cards in the deck
   int cards = 0;
   while (cards < 2) 
   {
      if (pre.deckCount[p] > 0)
      {
         int nextCard = pre.deck[p][pre.deckCount[p] - 1];
         // put in hand if found
         if (nextCard >= 4 && nextCard <= 6)
         {
            if (pre.handCount[p] <= MAX_HAND)
            {
               pre.handCount[p]++;
            }
            pre.hand[p][pre.handCount[p] - 1] = nextCard;
            pre.deckCount[p]--;
            cards++;
         }
         else // put in discard
         {
            pre.discardCount[p]++;
            pre.discard[p][pre.discardCount[p] - 1] = nextCard;
            pre.deckCount[p]--;
         }
      }
      else  // take shuffled cards from deck
      {
         memcpy(pre.deck[p], post->deck[p], sizeof(int) * pre.discardCount[p]);
         memcpy(pre.discard[p], post->discard[p], sizeof(int)*pre.discardCount[p]);
         pre.deckCount[p] = post->deckCount[p];
         pre.discardCount[p] = post->discardCount[p];
      }
   }

   // add Adventurer card to discard and remove from hand
   pre.discardCount[p]++;
   pre.hand[p][handPos] = pre.hand[p][pre.handCount[p] -1];
   pre.handCount[p]--;

   // check if number of cards are correct
   if (memcmp(&pre, post, sizeof(struct gameState)) != 0)
   {
      int countPre = 0;
      int countPost = 0;

      // check how many treasure cards in hand
      for (int i = 0; i < pre.handCount[p]; i++)
      {
         if (pre.hand[p][i] >= 4 && pre.hand[p][i] <= 6)
         {
            countPre++;
         }
      }
      for (int i = 0; i < post->handCount[p]; i++)
      {
         if (post->hand[p][i] >= 4 && post->hand[p][i] <= 6)
         {
            countPost++;
         }
      }

      printf("TEST FAILED\n");
      printf("Treasure Count: Expected: %d  Result: %d\n", countPre, countPost);
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

   printf("TESTING Adventurer card:\nRandom Tests:\n");

   for (n = 0; n < 1000; n++) {
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

      // add copper in two random places in the deck/discard pile (prevent infinite loop)
      for (k = 0; k < 22; k++)
      {
         int choice = floor(Random() * 2);
         int place;

         if (choice == 0)
         {
            place = floor(Random() * G.handCount[p]);
            G.hand[p][place] = 4;
         }
         else
         {
            place = floor(Random() * G.discardCount[p]);
            G.discard[p][place] = 4;
         }
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

      checkAdventurerCard(p, handPos, &G);
   }

   printf("End of random tests.\n\n");

   return 0;
}

