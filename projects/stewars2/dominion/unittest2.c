//
//  unittest2.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "minion_test.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include<stdlib.h>
#include <stdio.h>
#include<time.h>


void test_minion_option1(struct gameState* state, int kingdom[]) {
    // 2.1 Test option 1--gain 2 coins:
    
    // variables used in testing:
    int numActions;
    int coin_count;
    int hand_size;
    
    // save prior numActions of Player 0:
    numActions = state->numActions;
    // save prior coin count of Player 0:
    coin_count = state->coins;
    // save prior hand size of Player 0:
    hand_size = state->handCount[0];
    
    // call minion_card():
    minion_card(state, 0, 1, 0);
    
    // check if numActions was incremented properly:
    if(state->numActions != numActions+1) {
        printf("Bug: numActions not incremented (reference: 2.1).\n");
    }
    // check if Player 0's coin count was incremented by 2:
    if(state->coins != coin_count+2) {
        printf("Bug: Coin count not incremented properly (reference: 2.1).\n");
    }
    // check if Player 0's hand size was not decremented:
    if(state->handCount[0] != hand_size) {
        printf("Bug: Player 0's hand size changed (reference: 2.1).\n");
    }
}

void test_minion_option2(struct gameState* state, int kingdom[]) {
    // variables used in testing:
    int i;
    int numActions;
    int hand_size0;
    int hand_size1;
    int deck_size0;
    int deck_size1;
    int playedCardsCount;
    
    // 2.2.1 Player 1 has at least 5 cards in his hand:
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    // Have Player 1 draw 5 cards:
    for(i=0; i<5; i++) {
        drawCard(1, state);
    }
    
    // save prior numActions of Player 0:
    numActions = state->numActions;
    // save prior hand size of Player 0:
    hand_size0 = state->handCount[0];
    // save prior hand size of Player 1:
    hand_size1 = state->handCount[1];
    // save prior deck size of Player 0:
    deck_size0 = state->deckCount[0];
    // save prior deck size of Player 1:
    deck_size1 = state->deckCount[1];
    // save prior playedCardsCount:
    playedCardsCount = state->playedCardCount;
    
    // call minion_card():
    minion_card(state, 0, 0, 1);
    
    // check if numActions was incremented properly:
    if(state->numActions != numActions+1) {
        printf("Bug: numActions not incremented (reference: 2.2.1).\n");
    }
    // check if Player 0's hand size is 4:
    if(state->handCount[0] != 4) {
        printf("Bug: Player 0's hand size not 4 (reference: 2.2.1).\n");
    }
    // check if Player 1's hand size is 4:
    if(state->handCount[1] != 4) {
        printf("Bug: Player 1's hand size not 4 (reference: 2.2.1).\n");
    }
    // check if Player 0's deck size was decremented by 4:
    if(state->deckCount[0] != deck_size0-4) {
        printf("Bug: Player 0's deck size not decremented properly (reference: 2.2.1).\n");
    }
    // check if Player 1's deck size was decremented by 4:
    if(state->deckCount[1] != deck_size1-4) {
        printf("Bug: Player 1's deck size not decremented properly (reference: 2.2.1).\n");
    }
    // check if playedCardCount was incremented properly:
    if(state->playedCardCount != playedCardsCount+hand_size0+hand_size1) {
        printf("Bug: playedCardsCount not incremented properly (reference: 2.2.1).\n");
    }
    
    
    
    // 2.2.2 Player 1 has less than 5 cards in his hand:
    // re-initialize game (with 2 players and given kingdom cards):
    initializeGame(2, kingdom, rand(), state);
    
    // Have Player 1 draw 3 cards:
    for(i=0; i<4; i++) {
        drawCard(1, state);
    }
    
    // save prior numActions of Player 0:
    numActions = state->numActions;
    // save prior hand size of Player 0:
    hand_size0 = state->handCount[0];
    // save prior hand size of Player 1:
    hand_size1 = state->handCount[1];
    // save prior deck size of Player 0:
    deck_size0 = state->deckCount[0];
    // save prior deck size of Player 1:
    deck_size1 = state->deckCount[1];
    // save prior playedCardsCount:
    playedCardsCount = state->playedCardCount;
    
    // call minion_card():
    minion_card(state, 0, 0, 1);
    
    // check if numActions was incremented properly:
    if(state->numActions != numActions+1) {
        printf("Bug: numActions not incremented (reference: 2.2.2).\n");
    }
    // check if Player 0's hand size is 4:
    if(state->handCount[0] != 4) {
        printf("Bug: Player 0's hand size not 4 (reference: 2.2.2).\n");
    }
    // check if Player 1's hand size is unchanged:
    if(state->handCount[1] != hand_size1) {
        printf("Bug: Player 1's hand size changed (reference: 2.2.2).\n");
    }
    // check if Player 0's deck size was decremented by 4:
    if(state->deckCount[0] != deck_size0-4) {
        printf("Bug: Player 0's deck size not decremented properly (reference: 2.2.2).\n");
    }
    // check if Player 1's deck size is unchanged:
    if(state->deckCount[1] != deck_size1) {
        printf("Bug: Player 1's deck size changed (reference: 2.2.2).\n");
    }
    // check if playedCardCount was incremented properly:
    if(state->playedCardCount != playedCardsCount+hand_size0) {
        printf("Bug: playedCardsCount not incremented properly (reference: 2.2.2).\n");
    }
}

int test_minion() {
    printf("----------------- Testing Minion Card (Refactored) ----------------\n");
    
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
                4.2.1 state->handCount[1] = 0;
        4. Initialize player's discard piles as empty
            4.1 state->discardCount[i] = 0;
        5. Initialize Player 0's turn:
            5.1 state->whoseTurn = 0;
            5.2 state->numActions = 1;
            5.3 state->numBuys = 1;
        6. state->playedCardCount = 0;
    */
    
    
// 2. Call minion_card() function and assert results:
    
    // 2.1 Test option 1--gain 2 coins:
    test_minion_option1(state, kingdom);
    
    // 2.2 Test option 2--discard hand, draw 4 cards, and force all other players with at least 5 cards in their hand to also discard their hand and draw 4 cards:
    test_minion_option2(state, kingdom);
    
    
    printf("\n");
    return 0;
}
