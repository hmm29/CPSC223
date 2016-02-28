/* 
File: Subst16.c
Programmer: Harrison Miller
Description: 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "Subst16.h"

void parseFlags(char* flags, Ruleptr ruleptr)
{
    if(flags[0] != '-') {
	exit(EXIT_FAILURE);
    }

    int i;
    for(i = 1; i < strlen(flags); i++) { // strlen doesnt include null terminator
	if(flags[i] == 'g' || flags[i] == 'q' || flags[i] == 'r') {
		ruleptr->filter = flags[i];
	}

	else if(flags[i] == 'S' && flags[i+1]) {
    		ruleptr->onSuccessRuleIndex = (int) flags[i+1];
	}
 	else if(flags[i] == 'F' && flags[i+1]) {
    		ruleptr->onFailureRuleIndex = (int) flags[i+1];		
	}
   }

   if(!ruleptr->filter) {
	ruleptr->filter = 'q';
   }
}

int main(int argc, char *argv[])
{
    int i, ruleIdx = 0;
    int numRules = argc-1/3; // number of rules 
    Ruleptr rules[numRules]; // create an array of rule pointers
    Ruleptr currentRulePtr; // pointer to current rule

    // initialize rules array
    memset(rules, 0, numRules * sizeof(Ruleptr));

    /* Argument checking
     * Ensure correct number and type of arguments
     */

    if(!(strcmp(argv[0],"Subst16") == 0 || strcmp(argv[0], "./Subst16") == 0)) {
        fprintf(stderr, "Incorrect file name");
	exit(EXIT_FAILURE);
    }

    if(argc < 4) {
	fprintf(stderr, "Incorrect number of arguments in %s", argv[0]);
        exit(EXIT_FAILURE);
    }

    /* Rule parsing 
     * Creates an array of pointers to rules in order 
     */
	
    for(i = 1; i < argc; i++) {
        if(i % 3 == 1) {
            /* error check for TO, make sure its a string and that it contains valid characters */
            currentRulePtr = malloc(sizeof(Rule)); // create new rule
	    currentRulePtr->FROM = argv[i];          
        }
        else if(i % 3 == 2) {
             /* error check for TO, make sure its a string and that it contains valid characters */
            currentRulePtr->TO = argv[i];
        }
        else if(i % 3 == 0) {
            /* error check for flags - make sure it starts with a dash and has no spaces/odd characters */
            parseFlags(argv[i], currentRulePtr);
            rules[ruleIdx++] = currentRulePtr;
        }
    }

    // FROM wildcard parsing 

    // TO insert matched character parsing


    /* Read from stdin and apply filters */

    int c;
    int j = 0;
    currentRulePtr = rules[j];

/*    while((c = getchar()) != EOF) {
	switch(currentRulePtr->filter) {

	case 'g':



	break;



	case 'q':

	if(c == currentRulePtr->FROM[0] && currentRulePtr->numFilters < 1) {
		int i;
		char *FROM = currentRulePtr->FROM;

		for (i = 1; i < strlen(FROM); i++) {
			if((c = getchar()) != FROM[i]) {
				ungetchar(c);
				break;
			}
		}
	}

	break;


	case 'r':



	break;



	}
    } */

    return EXIT_SUCCESS;
}
