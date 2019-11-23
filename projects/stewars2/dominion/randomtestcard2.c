//
//  minion_random_test.c
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
        // for calling minion_card():
        int current_player;
        int choice1;
        int choice2;
        int handPos;
        int playedCardsCount;
        // for asserts:
        int numActions;
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
        
        // have all other players (i.e. all players except Player 0) draw 5 cards from their deck:
        for(j=1; j<numPlayers; j++) {
            for(k=0; k<5; k++) {
                drawCard(j, state);            }
        }
        
        
        // 2. Randomize variables for minion_card():
        
        // randomize current player in range [0, numPlayers-1]:
        current_player = rand() % numPlayers;
        state->whoseTurn = current_player;
        // update current player's coin coint (with 0 bonus coins):
        updateCoins(current_player, state, 0);
        
        // randomize option (choice1, choice2) for Minion card in range [0, 1]:
        choice1 = rand() % 2;
        // choice 2 = not(choice1):
        choice2 = (choice1+1) % 2;
        
        // randomize hand position of current card for current player:
        handPos = rand() % state->handCount[current_player];
        
        // randomize if all players except current player have at least 5 cards in their hand:
        int at_least_5_cards;
        int num_cards;
        for(j=0; j<numPlayers; j++) {
            // if not current player:
            if(j!=current_player) {
                at_least_5_cards = rand() % 2;
                // make Player j have less than 4 cards in his hand:
                if(at_least_5_cards==0) {
                    // randomize number of cards in Player j's hand in range [0, 4];
                    num_cards = rand() % 5;
                    // discard (5 - num_cards) cards from Player j's hand:
                    for(k=num_cards; k<5; k++) {
                        discardCard(0, j, state, 0);
                    }
                }
                // otherwise, Player j has 5 cards in  his hand:
            }
            // printf("%d ", state->handCount[j]);
        }
        
        
         // 3. save variables for minion_card() and call function:
        
        // arrays used in testing (dependent on numPlayers):
        int hand_size[numPlayers];
        int deck_size[numPlayers];
        
        // save prior numActions of current player:
        numActions = state->numActions;
        // save prior coin count of current player:
        coin_count = state->coins;
        // save prior playedCardsCount:
        playedCardsCount = state->playedCardCount;
        // save prior hand sizes of all players:
        for(j=0; j<numPlayers; j++) {
            hand_size[j] = state->handCount[j];
        }
        // save prior deck sizes of all players:
        for(j=0; j<numPlayers; j++) {
            deck_size[j] = state->deckCount[j];
        }
        
        // call minion_card():
        minion_card(state, handPos, choice1, choice2);
        
        
        // 4. Asserts:
        
        // check if numActions was incremented properly:
        if(state->numActions != numActions+1) {
            printf("Bug: numActions not incremented.\n");
        }
        
        // 4.1 Option 1--gain 2 coins:
        if(choice1==1) {
            // check if current player's coin count was incremented by 2:
            if(state->coins != coin_count+2) {
                printf("Bug: Coin count not incremented properly (reference: option = 1).\n");
            }
            // check if current player's hand size was decremented by 1 (for discarding current card):
            if(state->handCount[current_player] != hand_size[current_player]-1) {
                printf("Bug: Current player's hand size not decremented properly (reference: option = 1).\n");
            }
        }
        // 4.2 Option 2--discard hand, draw 4 cards, and force all other players with at least 5 cards in their hand to also discard their hand and draw 4 cards:
        else {
            // check if current player's hand size is 4:
            if(state->handCount[current_player] != 4) {
                printf("Bug: Current player's hand size not 4 (reference: option = 2).\n");
            }
            // check if current player's deck size was decremented by 4:
            if(state->deckCount[current_player] != deck_size[current_player]-4) {
                printf("Bug: Current player's deck size not decremented properly (reference: option = 2).\n");
            }
            // check hand and deck sizes of other players:
            for(j=0; j<numPlayers; j++) {
                // if not current player:
                if(j!=current_player) {
                    // if Player j had at least 5 cards in his hand (before calling minion_card()):
                    if(hand_size[j] >=5) {
                        // check if Player j's hand size is 4:
                        if(state->handCount[j] != 4) {
                            printf("Bug: Player %d's hand size not 4 (reference: option = 2).\n", j);
                        }
                        // check if Player j's deck size was decremented by 4:
                        if(state->deckCount[j] != deck_size[j]-4) {
                            printf("Bug: Player %d's deck size not decremented properly (reference: option = 2).\n", j);
                        }
                    }
                }
            }
        }
        
        
        printf("\n");
    }
    
    
    printf("\n");
    return 0;
}
