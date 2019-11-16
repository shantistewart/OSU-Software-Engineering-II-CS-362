//
//  unittest1.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "baron_test.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void test_baron_option2(struct gameState* state, int kingdom[], int option1) {
    // variables used in testing:
    int choice1 = 0;
    int numBuys;
    int estate_num;
    int i;
    
    // 2.2.1 With 8 Estate cards in supply pile:
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    if(option1==1) {
        // 2.1.2.1 With 0 Estate cards in hand:
        option1 = 1;
        
        // Delete Player 0's hand:
        state->handCount[0] = 0;
        // Fill Player 0's hand with 5 Copper cards:
        for(i=0; i<5; i++) {
            state->hand[0][state->handCount[0]] = copper;
            state->handCount[0]++;
        }
    }
    
    // save prior numBuys of Player 0:
    numBuys = state->numBuys;
    // save prior Estate card supply count:
    estate_num = state->supplyCount[estate];
    
    // call baron_card():
    baron_card(state, choice1);
    
    // check if numBuys was incremented properly:
    if(state->numBuys != numBuys+1) {
        printf("Bug: numBuys not incremented properly (reference: 2.2.1, choice1 = %d).\n", option1);
    }
    // check if Player 0's discard pile size was incremented to 1:
    if(state->discardCount[0] != 1) {
        printf("Bug: Discard pile size not incremented properly (reference: 2.2.1, choice1 = %d).\n", option1);
    }
    // check if 1 Estate card was placed in Player 0's discard pile:
    if(state->discard[0][state->discardCount[0]-1] != estate) {
        printf("Bug: Estate card not placed in discard pile (reference: 2.2.1, choice1 = %d).\n", option1);
    }
    // check if Estate card supply count was decremented properly:
    if(state->supplyCount[estate] != estate_num-1) {
        printf("Bug: Estate card supply count not decremented properly (reference: 2.2.1, choice1 = %d).\n", option1);
    }
    
    // 2.2.2 With 0 Estate cards in supply pile:
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    if(option1==1) {
        // 2.1.2.2 With 0 Estate cards in hand:
        option1 = 1;
        
        // Delete Player 0's hand:
        state->handCount[0] = 0;
        // Fill Player 0's hand with 5 Copper cards:
        for(i=0; i<5; i++) {
            state->hand[0][state->handCount[0]] = copper;
            state->handCount[0]++;
        }
    }
    
    // set Estate card supply count to 0:
    state->supplyCount[estate] = 0;
    // save prior numBuys of Player 0:
    numBuys = state->numBuys;
    
    // call baron_card():
    baron_card(state, choice1);
    
    // check if numBuys was incremented properly:
    if(state->numBuys != numBuys+1) {
        printf("Bug: numBuys not incremented properly (reference: 2.2.2, choice1 = %d).\n", option1);
    }
    // check if Player 0's discard pile size is still 0:
    if(state->discardCount[0] != 0) {
        printf("Bug: Discard pile size incremented (reference: 2.2.2, choice1 = %d).\n", option1);
    }
    // check if Estate card supply count is still 0:
    if(state->supplyCount[estate] != 0) {
        printf("Bug: Estate card supply not zero (reference: 2.2.2, choice1 = %d).\n", option1);
    }
}

void test_baron_option1(struct gameState* state, int kingdom[]) {
    // variables used in testing:
    int numBuys;
    int hand_size;
    int coin_count;
    
    // 2.1.1 With at least 1 Estate card in hand:
    // Add Estate card to Player 0's hand:
    gainCard(estate, state, 2, 0);
    // save prior numBuys of Player 0:
    numBuys = state->numBuys;
    // save prior hand size of Player 0:
    hand_size = state->handCount[0];
    // save prior coin count of Player 0:
    coin_count = state->coins;
    
    // call baron_card():
    baron_card(state, 1);
    
    // check if numBuys was incremented properly:
    if(state->numBuys != numBuys+1) {
        printf("Bug: numBuys not incremented (reference: 2.1.1).\n");
    }
    // check if Player 0's discard pile size was incremented to 1:
    if(state->discardCount[0] != 1) {
        printf("Bug: Discard pile size not incremented properly (reference: 2.1.1).\n");
    }
    // check if 1 Estate card was placed in Player 0's discard pile:
    if(state->discard[0][state->discardCount[0]-1] != estate) {
        printf("Bug: Estate card not placed in discard pile (reference: 2.1.1).\n");
    }
    // check if Player 0's hand size was decremented properly:
    if(state->handCount[0] != hand_size-1) {
        printf("Bug: Hand size not decremented properly (reference: 2.1.1).\n");
    }
    // check if Player 0's coin count was incremented by 4:
    if(state->coins != coin_count+4) {
        printf("Bug: Coin count not incremented properly (reference: 2.1.1).\n");
    }
    
    // 2.1.2 With 0 Estate cards in hand:
    // test option 2 (with choice1 = 1):
    test_baron_option2(state, kingdom, 1);
}

int test_baron() {
    printf("----------------- Testing Baron Card (Refactored) ----------------\n");
    
    srand(time(NULL));
    
// 1. Initialize varables:
    // set up game state variable:
    struct gameState* state = newGame();
    
    // set kingdom cards:
    int kingdom[10] = {baron, minion, ambassador, tribute, mine, adventurer, council_room, feast, gardens, remodel};
    
    // initialize game with 2 players and given kingdom cards:
    initializeGame(2, kingdom, rand(), state);
    /* relevant variable initializations:
        1. state->numPlayers = 2
        2. Initializes number of Victory cards:
            2.1 state->supplyCount[estate] = 8;
            2.2 state->supplyCount[duchy] = 8;
            2.3 state->supplyCount[province] = 8;
        3. Initializes player's decks:
            3.1 state->deckCount[i] = 10;
            3.1 Each player gets 3 Estate cards (in state->deck[i][j])
            3.2 Each player gets 7 Copper cards (in state->deck[i][j])
            3.3 Players' decks are shuffled.
        4. Initializes player's hands:
            4.1 Player 0's hand gains 5 (random) cards from his deck.
                4.1.1 state->handCount[0] = 5;
                4.1.2 state->deckCount[0] = 5;
            4.2 Player 1's hand is initialized as empty.
                4.2.1 state->handCount[1] = 0;
        5. Initialize player's discard piles as empty
            5.1 state->discardCount[i] = 0;
        6. Initialize Player 0's turn:
            6.1 state->whoseTurn = 0;
            6.2 state->numActions = 1;
            6.3 state->numBuys = 1;
    */
    // testing initializeGame:
    /*
    printf("Number of players: %d\n", state->numPlayers);
    printf("Number of Estate, Duchy, and Province cards: %d, %d, %d\n", state->supplyCount[estate], state->supplyCount[duchy], state->supplyCount[province]);
    printf("Player 0's deck:");
    for(i=0; i<state->deckCount[0]; i++) {
        printf(" %d", state->deck[0][i]);
    }
    printf("\nPlayer 1's deck:");
    for(i=0; i<state->deckCount[1]; i++) {
        printf(" %d", state->deck[1][i]);
    }
    printf("\nPlayer 0's hand:");
    for(i=0; i<state->handCount[0]; i++) {
        printf(" %d", state->hand[0][i]);
    }
    printf("\nPlayer 1's hand size: %d\n", state->handCount[1]);
    printf("Player 0 and Player 1's discard pile size: %d, %d\n", state->discardCount[0], state->discardCount[1]);
    printf("Player 0's number of actions and number of buys: %d, %d\n", state->numActions, state->numBuys);
    */
    
    
// 2. Call baron_card() function and assert results:
    
    // 2.1 Test option 1--discard an estate for 4 coins:
    test_baron_option1(state, kingdom);
    
    // 2.2 Test option 2--gain an estate:
    test_baron_option2(state, kingdom, 0);
    
    
    printf("\n");
    return 0;
}
