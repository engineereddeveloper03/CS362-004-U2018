/* -----------------------------------------------------------------------
*
* Include the following lines in  makefile:
*
* cardtest2: cardtest2.c dominion.o rngs.o
*      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

struct gameState * resetGame(int k[], int seed, int players) {
	struct gameState * g;
	//create/reset a game
	g = malloc(sizeof(struct gameState) * 1);

	//init game
	initializeGame(players, k, seed, g);
	//create a copy of the game


	return g;

}

//int adventurerEffect(int drawntreasure, int currentPlayer, struct gameState *state, int temphand[]) {
//
//	//******BUG******
//	int z;
//	int cardDrawn;
//	while (drawntreasure<2) {
//		if (state->deckCount[currentPlayer] <1) {//if the deck is empty we need to shuffle discard and add to deck
//			shuffle(currentPlayer, state);
//		}
//		drawCard(currentPlayer, state);
//		cardDrawn = state->hand[currentPlayer][state->handCount[currentPlayer] - 1];//top card of hand is most recently drawn card.
//		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
//			drawntreasure++;
//		else {
//			temphand[z] = cardDrawn;
//			state->handCount[currentPlayer]--; //this should just remove the top card (the most recently drawn one).
//			z++;
//		}
//	}
//	while (z - 1 >= 0) {
//		state->discard[currentPlayer][state->discardCount[currentPlayer]++] = temphand[z - 1]; // discard all cards in play that have been drawn
//		z = z - 1;
//	}
//	return 0;
//}
#define NOISY_TEST 1
//testing adventurer
//adventurer doesn't discard itself?
#define TREASUREGAINS 2
#define HAND 2
int main() {
	struct gameState * testG;
	int kingdom[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int seed = 1000;
	int begHand;
	int newHand;
	int i;
	int temphand[MAX_HAND];
	testG = resetGame(kingdom, seed, 2);

	printf("Testing adventurer card\n\n");

	begHand = testG->handCount[0];
#if NOISY_TEST
	printf("Beginning hand count is %d\n", begHand);
	printf("hand of player 1 before adventurer is:");
#endif

	for (i = 0; i < testG->handCount[0]; i++) {
		printf(" %d", testG->hand[0][i]);
	}
	printf("\n\n");
	//gain the aventurer card
	gainCard(adventurer, testG, HAND, 0);
	adventurerEffect(0, 0, testG, temphand);
	newHand = testG->handCount[0];
	printf("Ending hand count is %d\n", newHand);
	printf("hand of player 1 after adventurer is:");
	for (i = 0; i < testG->handCount[0]; i++) {
		printf(" %d", testG->hand[0][i]);
	}
	//check new hand
	if (newHand == (TREASUREGAINS + begHand)) {
		printf("Ending hand count is %d\n", newHand);
		printf("hand of player 1 after adventurer is:");
		for (i = 0; i < testG->handCount[0]; i++) {
			printf(" %d", testG->hand[0][i]);
		}
		printf("\nTest passed\n");
	}
	else {
		printf("\nTest failed\n");
	}
}
