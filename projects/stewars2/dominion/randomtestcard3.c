//
//  tribute_random_test.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/17/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RAND_TESTS 1000


int main() {
    printf("----------------- Random Test for Minion Card (Refactored) ----------------\n");
    
    srand(time(NULL));
    
    // variables used in testing:
        // for calling initializeGame():
        int numPlayers;
        int kingdom[10];
        int result;
        // for calling tribute_card():
        int current_player;
        int nextPlayer;
        int card;
        int deck_size;
        int discard_size;
        // for asserts:
        int numActions;
        int coin_count;
        int hand_size_current;
        int deck_size_next;
        int discard_size_next;
        // for loop variables:
        int i;
        int j;
        int k;
    
    // declare game state variable:
    struct gameState* state = newGame();
    
    // random testing:
    for(i=0; i<RAND_TESTS; i++) {
        printf("Iteration: %d\n", i+1);
        // 1. Initialize random game:
        
        // randomize number of players in range [2, MAX_PLAYERS]:
        numPlayers = (rand() % (MAX_PLAYERS-1)) + 2;
        
        // randomize distinct kingdom cards in range [adventurer, treasure_map] = [7, 26]:
        for(j=0; j<10; j++) {
            int distinct = 0;
            while(distinct==0) {
                // random card in range [adventurer, treasure_map]:
                kingdom[j] = (rand() % (treasure_map - adventurer + 1)) + adventurer;
                // check if card is different from all previous cards:
                distinct = 1;
                for(k=0; k<j; k++) {
                    if(kingdom[j] == kingdom[k]) {
                        distinct = 0;
                    }
                }
            }
        }
        
        // initialize game with randomized number of players and randomized kingdom cards:
        result = initializeGame(numPlayers, kingdom, rand(), state);
        // check that initializeGame did now throw an error:
        if(result!=0) {
            printf("initializeGame() threw an error.\n");
        }
        
        
        // 2. Randomize/save variables for tribute_card():
        
        // randomize current player in range [0, numPlayers-1]:
        current_player = rand() % numPlayers;
        state->whoseTurn = current_player;
        // update current player's coin coint (with 0 bonus coins):
        updateCoins(current_player, state, 0);
        // set next player:
        if(current_player == numPlayers-1) {
            nextPlayer = 0;
        }
        else {
            nextPlayer = current_player + 1;
        }
        
        // randomize all player's deck size and deck:
        for(j=0; j<numPlayers; j++) {
            // delete deck:
            state->deckCount[j] = 0;
            // randomize size of deck in range [0,10]:
            deck_size = rand() % 11;
            // fill deck with random (valid) cards:
            for(k=0; k<deck_size; k++) {
                // random (valid) card in range [curse, treasure_map] = [0, 26]:
                card = rand() % 27;
                state->deck[j][k] = card;
                // increment deck size of Player j:
                state->deckCount[j]++;
            }
        }
        
        // randomize all player's discard pile size:
        for(j=0; j<numPlayers; j++) {
            // delete discard pile:
            state->discardCount[j] = 0;
            // randomize size of discard pile in range [0,10]:
            discard_size = rand() % 11;
            // fill discard pile with random (valid) cards:
            for(k=0; k<discard_size; k++) {
                // random (valid) card in range [curse, treasure_map] = [0, 26]:
                card = rand() % 27;
                state->discard[j][k] = card;
                // increment discard pile size of Player j:
                state->discardCount[j]++;
            }
        }
        
        
        // 3. save variables for tribute_card() and call function:
        
        // save prior numActions of current player:
        numActions = state->numActions;
        // save prior coin count of current player:
        coin_count = state->coins;
        // save current player's prior hand size:
        hand_size_current = state->handCount[current_player];
        // save next player's prior deck size:
        deck_size_next = state->deckCount[nextPlayer];
        // save next player's prior discard pile size:
        discard_size_next = state->discardCount[nextPlayer];
                
        // call tribute_card:
        tribute_card(state);
        
        
        // 4. Asserts:
        
        // check if deck and discard pile sizes of next player were decremented properly:
        if(deck_size_next >= 2) {       // if next player's deck size was >=2:
            // check if next player's deck size was decremented by 2:
            if(state->deckCount[nextPlayer] != deck_size_next-2) {
                printf("Bug: Next player's deck size not decremented properly.\n");
            }
        }
        else if(deck_size_next == 1) {      // if next player's deck size was 1:
             // check if next player's deck size was decremented by 1:
            if(state->deckCount[nextPlayer] != deck_size_next-1) {
                printf("Bug: Next player's deck size not decremented properly.\n");
            }
            if(discard_size_next >= 1) {
                // check if next player's discard pile size was decremented by 1:
                if(state->discardCount[nextPlayer] != discard_size_next-1) {
                    printf("Bug: Next player's discard pile size not decremented properly.\n");
                }
            }
        }
        else {      // if next player's deck size was 0:
            // check if next player's discard pile size is 0 (entire discard pile moved to deck):
            if(state->discardCount[nextPlayer] != 0) {
                printf("Bug: Next player's discard pile size not 0.\n");
            }
        }
        
        
        printf("\n");
    }
    
    printf("\n");
    return 0;
}
