//
//  tribute_test.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "tribute_test.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include<stdlib.h>
#include <stdio.h>
#include<time.h>


int test_tribute() {
    printf("----------------- Testing Tribute Card (Refactored) ----------------\n");
    
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
    
    
    printf("\n");
    return 0;
}
