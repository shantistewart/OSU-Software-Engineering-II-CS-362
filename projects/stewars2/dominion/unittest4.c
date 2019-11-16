//
//  tribute_test.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "mine_test.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include<stdlib.h>
#include <stdio.h>
#include<time.h>


void test_mine_inputs(struct gameState* state, int kingdom[], int trash_card, int choice2, int valid) {
    // variables used in testing:
    int result;
    int choice1;
    int handPos;
    int hand_size;
    int num_choice1_prior = 0;
    int num_choice2_prior = 0;
    int num_choice1_now = 0;
    int num_choice2_now = 0;
    int i;
    
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    // Insert 1 Mine card into (top-1 of) Player 0's hand:
    state->hand[0][3] = mine;
    // set Mine card as current card:
    handPos = 3;
    // Insert 1 trash_card into (top of) Player 0's hand:
    state->hand[0][4] = trash_card;
    // set choice1 as index of trash_card:
    choice1 = 4;
    
    // save prior hand size of Player 0:
    hand_size = state->handCount[0];
    // find and save prior number of choice1 cards in Player 0's hand:
    for(i=0; i<state->handCount[0]; i++) {
        if(state->hand[0][i] == trash_card) {
            num_choice1_prior++;
        }
    }
    // find and save prior number of choice2 cards in Player 0's hand:
    for(i=0; i<state->handCount[0]; i++) {
        if(state->hand[0][i] == choice2) {
            num_choice2_prior++;
        }
    }
    
    // call mine_card():
    result = mine_card(state, handPos, choice1, choice2);
    // check if mine_card() did not throw an error (for valid inputs):
    if(valid==1) {
        if(result!=0) {
            printf("Bug: ambassador_card() threw an error (reference: 2.1, trash_card=%d, gain_card=%d).\n", trash_card, choice2);
            return;
        }
    }
    // check if mine_card() threw an error (for invalid inputs):
    else {
        if(result!=-1) {
            printf("Bug: ambassador_card() did not throw an error (reference: 2.1, trash_card=%d, gain_card=%d).\n", trash_card, choice2);
        }
        return;
    }
    
    // find and save current number of choice1 cards in Player 0's hand:
    for(i=0; i<state->handCount[0]; i++) {
        if(state->hand[0][i] == trash_card) {
            num_choice1_now++;
        }
    }
    // find and save current number of choice2 cards in Player 0's hand:
    for(i=0; i<state->handCount[0]; i++) {
        if(state->hand[0][i] == choice2) {
            num_choice2_now++;
        }
    }
    
    // check that Player 0's hand size is unchanged:
    if(state->handCount[0] != hand_size) {
        printf("Bug: Player 0's hand size changed (reference: 2.1, trash_card=%d, gain_card=%d).\n", trash_card, choice2);
    }
    // check that 1 choice1 card was removed from Player 0's hand:
    if(num_choice1_now != num_choice1_prior-1) {
        printf("Bug: card not trashed (reference: 2.1, trash_card=%d, gain_card=%d).\n", trash_card, choice2);
    }
    // check that 1 choice2 card was added to Player 0's hand:
    if(num_choice2_now != num_choice2_prior+1) {
        printf("Bug: card not gained (reference: 2.1, trash_card=%d, gain_card=%d).\n", trash_card, choice2);
    }
}


int test_mine() {
    printf("----------------- Testing Mine Card (Refactored) ----------------\n");
    
    srand(time(NULL));
    
    // variables used in testing:
    int trash_card;
    int choice2;
    int valid;
    
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
    
    
// 2. Call mine_card() function and assert results:
    
    // 2.1 Test with valid inputs (choice1 and choice2):
    valid = 1;
    
    // 2.1.1 Test with Copper card to be trashed and Silver card to be gained:
    trash_card = copper;
    choice2 = silver;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    // 2.1.2 Test with Silver card to be trashed and Gold card to be gained:
    trash_card = copper;
    choice2 = gold;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    // 2.2 Test with invalid inputs (choice1 and choice2):
    valid = 0;
    
    // 2.2.1 Test with choice2 not a valid Dominion card:
    trash_card = copper;
    choice2 = treasure_map+1;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    // 2.2.2 Test with choice2 not a Treasure card:
    trash_card = copper;
    choice2 = mine;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    // 2.2.3 Test with trash_card not a Treasure card (cost(curse) = 0):
    trash_card = curse;
    choice2 = silver;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    // 2.2.4 Test with too expensive of a card to be gained:
    trash_card = copper;
    choice2 = gold;
    test_mine_inputs(state, kingdom, trash_card, choice2, valid);
    
    
    printf("\n");
    return 0;
}
