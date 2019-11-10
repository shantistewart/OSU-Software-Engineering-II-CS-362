//
//  main.c
//  Random_Testing_Quiz
//
//  Created by Shanti Stewart on 11/9/19.
//  Copyright © 2019 CS 362. All rights reserved.
//


#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>


char inputChar() {
	// random ASCII code in the range [0,127] = valid ASCII characters:
	int num = rand() % 128;
	// convert code to character:
	char c = num;
	
    return c;
}

char inputCharLowercase() {
	// random ASCII code in the range [97,122] = lowercase alphabet letters:
	int num = (rand() % 26) + 97;
	// convert code to character:
	char c = num;
	
    return c;
}

char* inputString() {
	// create string of length 6 characters (including null character at end):
    char *str = (char *) malloc(sizeof(char) * 6);

	// fill string with 5 random characters:
	for(int i=0; i<5; i++) {
		str[i] = inputCharLowercase();
	}
	// end string with null character:
    str[5] = '\0';
	
    return str;
}

void testme() {
	int tcCount = 0;
	char* s;
	char c;
	int state = 0;

	while (1) {
		tcCount++;
		c = inputChar();
		s = inputString();
		printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

		if (c == '[' && state == 0)
			state = 1;
		if (c == '(' && state == 1)
			state = 2;
		if (c == '{' && state == 2)
			state = 3;
		if (c == ' '&& state == 3)
			state = 4;
		if (c == 'a' && state == 4)
			state = 5;
		if (c == 'x' && state == 5)
			state = 6;
		if (c == '}' && state == 6)
			state = 7;
		if (c == ')' && state == 7)
			state = 8;
		if (c == ']' && state == 8)
			state = 9;
		if (s[0] == 'r' && s[1] == 'e' && s[2] == 's' && s[3] == 'e' && s[4] == 't' && s[5] == '\0' && state == 9) {
			printf("Error");
			exit(200);
		}
	}
}


int main() {
	srand(time(NULL));
	
	testme();
	
	// Testing inputString():
	/*
	for(int i=0; i<6; i++) {
		char* str = inputString();
		printf("%s\n", str);
	}
	*/
	
	printf("\n");
	return 0;
}
