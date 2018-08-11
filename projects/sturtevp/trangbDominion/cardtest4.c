/* -----------------------------------------------------------------------
*
* Include the following lines in  makefile:
*
* cardtest4: cardtest4.c dominion.o rngs.o
*      gcc -o cardtest4 -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
* -----------------------------------------------------------------------
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

//int cutpurseEffect(int currentPlayer, struct gameState * state, int handPos)

struct gameState * resetGame(int k[], int seed, int players) {
	struct gameState * g;
	//create/reset a game
	g = malloc(sizeof(struct gameState) * 1);

	//init game
	initializeGame(players, k, seed, g);
	//create a copy of the game
	return g;
}

#define NOISY_TEST 1
#define CUTPURSEGAIN 2
#define HAND 2
int main() {
	struct gameState * testG;
	//revised kingdom to include steward
	int kingdom[10] = { adventurer, gardens, embargo, village, minion, steward, cutpurse,
		sea_hag, tribute, smithy };
	int seed = 1000;
	int newHand;
	int oldHand;
	int numPlayers;
	int oldCoinCount;
	int newCoinCount;
	int j;
	int k;
	printf("TESTING CUTPURSE\n");
	for (numPlayers = 1; numPlayers < 4; numPlayers++) {
		//start/reset a game with numPlayers
		testG = resetGame(kingdom, seed, numPlayers+1);
		oldCoinCount = testG->coins;
		gainCard(cutpurse, testG, HAND, 0);
		printf("Original coins: %d\n", oldCoinCount);
		printf("BEFORE HAND: ");
		for (j = 0; j < testG->handCount[0]; j++) {
			printf(" %d", testG->hand[0][j]);
		}
		printf("\n\n");
		printf("Displaying opponent hands BEFORE cutpurse\n\n");
		oldHand = 5;
		int curturn;
		for (j = 1; j < numPlayers +1; j++) {
			endTurn(testG);
			curturn = whoseTurn(testG);
			printf("curturn %d\n", curturn);
			printf("Player %d: ", j +1);
			for (k = 0; k < testG->handCount[j]; k++) {
				printf(" %d", testG->hand[j][k]);
			}
			
			printf("\n\n");
		}
		endTurn(testG);
		printf("curturn %d\n", whoseTurn(testG));
		cutpurseEffect(0, testG, testG->handCount[0]);
		newCoinCount = testG->coins;
		printf("New coins: %d\n", newCoinCount);
		printf("new total pOne hand %d\n", testG->handCount[0]);
		newHand = testG->handCount[0];
		printf("AFTER HAND: ");
		for (j = 0; j < testG->handCount[0]; j++) {
			printf(" %d", testG->hand[0][j]);
		}
		if (newHand == oldHand) {
			printf("TEST PASSED for pOne hand count\n");
		}
		else {
			printf("TEST FAILED for pOne hand count\n");
		}
		printf("\n\nDisplaying opponent hands AFTER cutpurse\n\n");
		for (j = 1; j < numPlayers +1; j++) {
			endTurn(testG);
			printf("Player %d: ", j +1 );
			for (k = 0; k < testG->handCount[j]; k++) {
				printf(" %d", testG->hand[j][k]);
			}
			printf("\n\n");
			newHand = testG->handCount[j];
			if (newHand == oldHand-1) {
				printf("TEST PASSED for player %d hand count\n",j+1);
			}
			else {
				printf("TEST FAILED for player %d hand count\n",j+1);
			}
			
		}
		printf("\n");
		//for (i = 1; i < numPlayers; i++) {
		//	printf("player %d coin count: %d",i+1,)
		//}
		//printf("\n\n");
		free(testG);
	}
}