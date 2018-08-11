/* -----------------------------------------------------------------------
*
* Include the following lines in  makefile:
*
* cardtest3: cardtest3.c dominion.o rngs.o
*      gcc -o cardtest3 -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
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

#define NOISY_TEST 1
#define HAND 2
#define STEWARDCOINS 2
int main() {
	struct gameState * testG;
	//revised kingdom to include steward
	int kingdom[10] = { adventurer, gardens, embargo, village, minion, steward, cutpurse,
		sea_hag, tribute, smithy };
	int seed = 1000;
	int begHand;
	int newHand;
	int i;
	//int pt;
	int choice;
	int oldCoinCount;





	//int stewardEffect(int choice1, int choice2, int choice3, int currentPlayer, struct gameState *state, int handPos)

	printf("Testing steward with starting hands\n");
	for (choice = 1; choice <= 3; choice++) {

		testG = resetGame(kingdom, seed, 2);
		oldCoinCount = testG->coins;
		begHand = testG->handCount[0];

		//gain steward card to starting hand
		gainCard(steward, testG, HAND, 0);
		stewardEffect(choice, copper, copper, 0, testG, testG->handCount[0] - 1);
		newHand= testG->handCount[0];
		printf("hand of player 1 after steward is:");
		for (i = 0; i < testG->handCount[0]; i++) {
			printf(" %d", testG->hand[0][i]);
		}
		printf("\n");
		//decided to draw 2 cards
		if (choice == 1) {
			if (newHand == begHand+2) {
				printf("TEST PASSED\n");
			}
			else {
				printf("TEST FAILED\n");
			}
		}//gain two coins
		else if (choice == 2) {
			printf("CHECKING COINS\n");
			if (testG->coins == oldCoinCount + STEWARDCOINS) {
				printf("TEST PASSED\n");
			}
			else {
				printf("TEST FAILED\n");
			}
		}
		else {
			printf("TESTING CHOICE 3\n");
			printf("hand of player 1 after steward is:");
			for (i = 0; i < testG->handCount[0]; i++) {
				printf(" %d", testG->hand[0][i]);
			}
			printf("\n");
			if (newHand == begHand - 2) {
				printf("TEST PASSED\n");
			}
			else {
				printf("TEST FAILED\n");
			}
			for (i = 0; i < testG->handCount[0]; i++) {
				printf(" %d", testG->hand[0][i]);
			}
			printf("\n");
		}
		free(testG);
	}
	
}