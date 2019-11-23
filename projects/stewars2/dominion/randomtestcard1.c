//
//  baron_random_test.c
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
    printf("----------------- Random Test for Baron Card (Refactored) ----------------\n");
    
    srand(time(NULL));
    
    // variables used in testing:
        // for calling initializeGame():
        int numPlayers;
        int kingdom[10];
        int result;
        // for calling baron_card():
        int choice1;
        int estate_hand;
        int estate_supply;
        // for asserts:
        int numBuys;
        int estate_num;
        int hand_size;
        int coin_count;
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
        
        
        // 2. Randomize variables for baron_card():
        
        // randomize option (choice1) for Baron card in range [0, 1]:
        choice1 = rand() % 2;
        
        // randomize if Player 0 has at least 1 Estate card in hand:
        estate_hand = rand() % 2;
        // with at least 1 Estate card in hand:
        if(estate_hand==1) {
            // add Estate card to Player 0's hand:
            gainCard(estate, state, 2, 0);
        }
        // with 0 Estate cards in hand:
        else {
            // delete Player 0's hand:
            state->handCount[0] = 0;
            // fill Player 0's hand with 5 Copper cards:
            for(j=0; j<5; j++) {
                state->hand[0][state->handCount[0]] = copper;
                state->handCount[0]++;
            }
        }
        
        // randomize if there is at least 1 Estate card in supply:
        estate_supply = rand() % 2;
        // with 0 Estate cards in supply:
        if(estate_supply==0) {
            // set Estate card supply count to 0:
            state->supplyCount[estate] = 0;
        }
        // with at least 1 Estate card in supply:
        else {
            // set Estate card supply count to random number in range [1, 5]:
            state->supplyCount[estate] = (rand() % 5) + 1;
        }
        
        
        // 3. save variables for baron_card() and call function:
        
        // save prior numBuys of Player 0:
        numBuys = state->numBuys;
        // save prior Estate card supply count:
        estate_num = state->supplyCount[estate];
        // save prior hand size of Player 0:
        hand_size = state->handCount[0];
        // save prior coin count of Player 0:
        coin_count = state->coins;
        
        // call baron_card():
        baron_card(state, choice1);
        
        
        // 4. Asserts:
        
        // check if numBuys was incremented properly:
        if(state->numBuys != numBuys+1) {
            printf("Bug: numBuys not incremented.\n");
        }
        
        // 4.1 Option 1--discard an estate for 4 coins:
        if(choice1==1) {
            // with at least 1 Estate card in hand:
            if(estate_hand==1) {
                // check if Player 0's discard pile size was incremented to 1:
                if(state->discardCount[0] != 1) {
                    printf("Bug: Discard pile size not incremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if 1 Estate card was placed in Player 0's discard pile:
                if(state->discard[0][state->discardCount[0]-1] != estate) {
                    printf("Bug: Estate card not placed in discard pile (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if Player 0's hand size was decremented properly:
                if(state->handCount[0] != hand_size-1) {
                    printf("Bug: Hand size not decremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if Player 0's coin count was incremented by 4:
                if(state->coins != coin_count+4) {
                    printf("Bug: Coin count not incremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
            }
            // with 0 Estate cards in hand:
            else {
                // with at least 1 Estate card in supply:
                if(estate_supply==1) {
                    // check if Player 0's discard pile size was incremented to 1:
                    if(state->discardCount[0] != 1) {
                        printf("Bug: Discard pile size not incremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                    }
                    // check if 1 Estate card was placed in Player 0's discard pile:
                    if(state->discard[0][state->discardCount[0]-1] != estate) {
                        printf("Bug: Estate card not placed in discard pile (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                    }
                    // check if Estate card supply count was decremented properly:
                    if(state->supplyCount[estate] != estate_num-1) {
                        printf("Bug: Estate card supply count not decremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                    }
                }
                // with 0 Estate cards in supply:
                else {
                    // check if Player 0's discard pile size is still 0:
                    if(state->discardCount[0] != 0) {
                        printf("Bug: Discard pile size incremented (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                    }
                    // check if Estate card supply count is still 0:
                    if(state->supplyCount[estate] != 0) {
                        printf("Bug: Estate card supply not zero (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                    }
                }
            }
        }
        // 4.2 Option 2--gain an estate:
        else {
            // with at least 1 Estate card in supply:
            if(estate_supply==1) {
                // check if Player 0's discard pile size was incremented to 1:
                if(state->discardCount[0] != 1) {
                    printf("Bug: Discard pile size not incremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if 1 Estate card was placed in Player 0's discard pile:
                if(state->discard[0][state->discardCount[0]-1] != estate) {
                    printf("Bug: Estate card not placed in discard pile (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if Estate card supply count was decremented properly:
                if(state->supplyCount[estate] != estate_num-1) {
                    printf("Bug: Estate card supply count not decremented properly (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
            }
            // with 0 Estate cards in supply:
            else {
                // check if Player 0's discard pile size is still 0:
                if(state->discardCount[0] != 0) {
                    printf("Bug: Discard pile size incremented (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
                // check if Estate card supply count is still 0:
                if(state->supplyCount[estate] != 0) {
                    printf("Bug: Estate card supply not zero (reference: choice1 = %d, estate_hand = %d, estate_supply = %d).\n", choice1, estate_hand, estate_supply);
                }
            }

        }
        
        
        printf("\n");
    }
    
    
    printf("\n");
    return 0;
}
