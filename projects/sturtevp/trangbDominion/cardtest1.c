/* -----------------------------------------------------------------------
*
* Include the following lines in  makefile:
*
* cardtest1: cardtest1.c dominion.o rngs.o
*      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"


//testing smithy card

struct gameState * resetGame(int k[], int seed, int players) {
	struct gameState * g;
	//create/reset a game
	g = malloc(sizeof(struct gameState) * 1);

	//init game
	initializeGame(players, k, seed, g);
	//create a copy of the game


	return g;

}

//FOUND BUG ,

//WRONG CARD DRAW AMOUNT

#define SMITHYDRAW 3
#define HAND 2
#define NOISY_TEST 1
//int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
int main() {
	struct gameState * testG;
	int kingdom[10] = { adventurer, gardens, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy };
	int seed = 1000;
	int begHand;
	int newHand;
	int i;
	testG=resetGame(kingdom, seed, 2);

	printf("Testing Smithy card\n\n");

	begHand = testG->handCount[0];
#if NOISY_TEST
	printf("Beginning hand count is %d\n", begHand);
	printf("hand of player 1 before smithy is:");
#endif
	for (i = 0; i < testG->handCount[0]; i++) {
		printf(" %d", testG->hand[0][i]);
	}
	printf("\n");
	//gain the adventurer card to the player's hand
	gainCard(smithy, testG, HAND,0);
	smithyEffect(0, testG, smithy);
	newHand = testG->handCount[0];
#if NOISY_TEST
	printf("New hand count is %d \n", newHand);
	printf("hand of player 1 is:");
#endif
	for (i = 0; i < testG->handCount[0]; i++) {
		printf(" %d", testG->hand[0][i]);
	}
	printf("\n");

	if (newHand == (SMITHYDRAW + begHand)) {
		printf("Test passed\n");
	}
	else {
		printf("Test failed\n");
	}

	printf("\n\n Testing Smithy card completed \n\n");
}