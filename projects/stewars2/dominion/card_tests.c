//
//  card_tests.c
//  CS 362 Dominion
//
//  Created by Shanti Stewart on 11/15/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include "baron_test.h"
#include "minion_test.h"
#include "ambassador_test.h"
#include "tribute_test.h"
#include "mine_test.h"
#include <stdio.h>


int main() {
    printf("----------------- Testing 5 Refactored Card Functions ----------------\n\n\n");
    
    test_baron();
    test_minion();
    test_ambassador();
    test_tribute();
    test_mine();
    
    return 0;
}
