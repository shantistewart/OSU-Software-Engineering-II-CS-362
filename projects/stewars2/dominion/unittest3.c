//
//  ambassador_test.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "ambassador_test.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include<stdlib.h>
#include <stdio.h>
#include<time.h>


void test_ambassador_valid_inputs(struct gameState* state, int kingdom[], int numCards) {
    // variables used in testing:
    int result;
    int hand_index;
    int copper_supply_count;
    int hand_size0;
    int discard_size1;
    int i;
    
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    // save prior supply count of Copper cards:
    copper_supply_count = state->supplyCount[copper];
    // save prior hand size of Player 0:
    hand_size0 = state->handCount[0];
    // save prior discard pile size of Player 1:
    discard_size1 = state->discardCount[1];
    // find and save hand index of 1st copper card in Player 0's hand:
    for(i=0; i<state->handCount[0]; i++) {
        if(state->hand[0][i] == copper) {
            hand_index = i;
            break;
        }
    }
    
    // call ambassador_card():
    result = ambassador_card(state, 0, hand_index, numCards);
    // check if ambassador_card() did not throw an error:
    if(result==-1) {
        printf("Bug: ambassador_card() threw an error (reference: 2.1.%d).\n", numCards+1);
        return;
    }
    
    // check that supply count of Copper cards was properly changed:
    if(state->supplyCount[copper] != copper_supply_count+numCards-1) {
        printf("Bug: Supply count of Copper cards not properly incremented (reference: 2.1.%d).\n", numCards+1);
    }
    // check that Player 0's hand size was properly decremented:
    if(state->handCount[0] != hand_size0-numCards) {
        printf("Bug: Player 0's hand size not properly decremented (reference: 2.1.%d).\n", numCards+1);
    }
    // check that Player 1's discard pile size was incremented:
    if(state->discardCount[1] != discard_size1+1) {
        printf("Bug: Player 1's discard pile size not properly incremented (reference: 2.1.%d).\n", numCards+1);
    }
}

int test_ambassador() {
    printf("----------------- Testing Ambassador Card (Refactored) ----------------\n");
    
    srand(time(NULL));
    
    // variables used in testing:
    int result;
    
// 1. Initialize varables:
    // set up game state variable:
    struct gameState* state = newGame();
    
    // set kingdom cards:
    int kingdom[10] = {baron, minion, ambassador, tribute, mine, adventurer, council_room, feast, gardens, remodel};
    
    // initialize game with 2 players and given kingdom cards:
    initializeGame(2, kingdom, rand(), state);
    /* relevant variable initializations:
        1. state->numPlayers = 2
        2. Initializes player's decks:
            2.1 state->deckCount[i] = 10;
            2.1 Each player gets 3 Estate cards (in state->deck[i][j])
            2.2 Each player gets 7 Copper cards (in state->deck[i][j])
            2.3 Players' decks are shuffled.
        3. Initializes player's hands:
            3.1 Player 0's hand gains 5 (random) cards from his deck.
                3.1.1 state->handCount[0] = 5;
                3.1.2 state->deckCount[0] = 5;
            3.2 Player 1's hand is initialized as empty.
                3.2.1 state->handCount[1] = 0;
        4. Initialize player's discard piles as empty
            4.1 state->discardCount[i] = 0;
        5. Initialize Player 0's turn:
            5.1 state->whoseTurn = 0;
            5.2 state->numActions = 1;
            5.3 state->numBuys = 1;
    */
    
    
// 2. Call ambassador_card() function and assert results:
    
    // 2.1 Test with valid inputs (choice1 and choice2):
    
    // 2.1.1 Test returning 0 copies of chosen card to supply:
    test_ambassador_valid_inputs(state, kingdom, 0);
    
    // 2.1.2 Test returning 1 copy of chosen card to supply:
    test_ambassador_valid_inputs(state, kingdom, 1);
    
    // 2.1.3 Test returning 2 copies of chosen card to supply:
    test_ambassador_valid_inputs(state, kingdom, 2);
    
    // 2.2 Test with invalid inputs (choice1 and choice2):
    
    // 2.2.1 Test with choice2 out of range (i.e. choice2<0 or choice2>2):
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    // call ambassador_card():
    result = ambassador_card(state, 0, 0, 3);
    // check if ambassador_card() threw an error:
    if(result!=-1) {
        printf("Bug: ambassador_card() did not throw an error (reference: 2.2.1).\n");
    }
    
    // 2.2.2 Test with choice1 = handPos:
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    // call ambassador_card():
    result = ambassador_card(state, 5, 5, 2);
    // check if ambassador_card() threw an error:
    if(result!=-1) {
        printf("Bug: ambassador_card() did not throw an error (reference: 2.2.2).\n");
    }
    
    
    printf("\n");
    return 0;
}
