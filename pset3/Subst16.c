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

char *copylastn(char *dest,char *src,int n)
{
        strncpy(dest+(strlen(dest)-strlen(src)), src, strlen(src));
        return dest;
}

void parseFlags(char* flags, Ruleptr ruleptr)
{
    if(flags[0] != '-') {
	exit(EXIT_FAILURE);
    }

    int i;

     // default to -1 for next rule indices
    ruleptr->onSuccessRuleIndex = ruleptr->onFailureRuleIndex = -1;

    for(i = 1; i < strlen(flags); i++) { // strlen doesnt include null terminator
        
	if(flags[i] == 'g' || flags[i] == 'q' || flags[i] == 'r') {
		ruleptr->filter = flags[i];
	}
	else if(flags[i] == 'S') {
    		if(isdigit(flags[i+1])) {
                if(isdigit(flags[i+2])) {
                    int n;
                    char num[10]; // reasonable upper bound on length of index number
                    for(n = 0; isdigit(flags[i+1+n]); n++) { // account for indices > 9
                        num[n] = flags[i+1+n];
                    }
                    num[n] = '\0';
                    ruleptr->onSuccessRuleIndex = atoi(num);
                } 
                else ruleptr->onSuccessRuleIndex = flags[i+1]-'0';
            } // ascii numbers start at 48 ('0')
            else ruleptr->onSuccessRuleIndex = 0;
	}
 	else if(flags[i] == 'F') {
    		if(isdigit(flags[i+1])) {
                if(isdigit(flags[i+2])) {
                    int n;
                    char num[10]; // reasonable upper bound on length of index number
                    for(n = 0; isdigit(flags[i+1+n]); n++) { // account for indices > 9
                        num[n] = flags[i+1+n];
                    }
                    num[n] = '\0';
                    ruleptr->onFailureRuleIndex = atoi(num);
                } 
                else ruleptr->onFailureRuleIndex = flags[i+1]-'0';
            }
            else ruleptr->onFailureRuleIndex = 0;
	}
   }

   if(!ruleptr->filter) {
	ruleptr->filter = 'q';
   }
}

/* 
 * inputString: reads input from stdin and saves to character array   
 */

char *inputString(FILE* fp, size_t size){
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size); // initial size from size arg
    if(!str) return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';
    return realloc(str, sizeof(char)*len);
}

/* 
 * str_replace: finds a substring and replaces all `from` occurrences with `to` according to flag specifier
 */
char *str_replace(char *orig, char *from, char *to, char flag) {
    char *result = NULL; /* the return string */
    char *ins = NULL;    /* the next insert point */
    char *tmp = NULL;    /* temporary */
    int len_from;  /* length of from */
    int len_to; /* length of to */
    int len_front; /* distance between from and end of last from */
    int count;    /* number of replacements */

    if (!orig)
        return NULL;
    if (!from)
        from = "";
    len_from = strlen(from);
    if (!to)
        to = "";
    len_to = strlen(to);

    if(flag == 'g' || flag == 'q') {
        ins = orig;
        for (count = 0; (tmp = strstr(ins, from)); ++count) {
            if(flag == 'q' && count == 1) {
               break;
            }
            ins = tmp + len_from;
        }

        tmp = result = malloc(strlen(orig) + (len_to - len_from) * count + 1);

        if (!result) return NULL;

        while (count--) {
            ins = strstr(orig, from);
            len_front = ins - orig;
            tmp = strncpy(tmp, orig, len_front) + len_front;
            tmp = strcpy(tmp, to) + len_to;
            orig += len_front + len_from; // move to next "end of from"
        }
        strcpy(tmp, orig);
    }
    else if(flag == 'r') {
        tmp = result = malloc(strlen(orig) + (len_to - len_from));
        if (!result) return NULL;
       tmp = strcpy(tmp, orig);

        while(strstr(tmp, from)) { // while there is a leftmost occurrence of from
            ins = strstr(tmp, from);
            tmp = str_replace(tmp + (ins-tmp), from, to, 'q');
            result = copylastn(result, tmp, strlen(tmp));
        }
        // printf("last result IS awesomely %s.\n", result);
    }

    return result;
}

int main(int argc, char *argv[])
{
    int i;
    int numRules = (argc-1)/3; // number of rules 
    int ruleIdx = 0; // index of rule (ptr) in array of rule pointers 
    Ruleptr rules[numRules]; // create an array of rule pointers
    Ruleptr currentRulePtr; // pointer to current rule

    //printf("NUM RULES IS %d\n", numRules);

    // initialize rules array
    memset(rules, 0, numRules * sizeof(Ruleptr));

    /* Argument checking
     * Ensure correct number and type of arguments
     */

    if(!(strcmp(argv[0],"Subst16") == 0 || strcmp(argv[0], "./Subst16") == 0)) {
        fprintf(stderr, "Incorrect file name.\n");
	    exit(EXIT_FAILURE);
    }

    if(argc < 4 || (argc-1)%3 > 0) {
	    fprintf(stderr, "Incorrect number of arguments in %s.\n", argv[0]);
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

    /* Read from stdin and apply filters */

    int j = 0;
    currentRulePtr = rules[j];
    char *input;

    // read input and save to char array
    input = inputString(stdin, 10);
    char *res;

    for(int i = 0; i < strlen(input); i++) {
        res = str_replace(input, currentRulePtr->FROM, currentRulePtr->TO, currentRulePtr->filter);

        if (strcmp(input, res) == 0) {  // if no change
            if(currentRulePtr->onFailureRuleIndex < numRules && currentRulePtr->onFailureRuleIndex > -1) {
                currentRulePtr = rules[currentRulePtr->onFailureRuleIndex];
                j = currentRulePtr->onFailureRuleIndex;
            } 
            // if no Sn or Fm rule specified, go to next rule if it exists
            else if(currentRulePtr->onFailureRuleIndex == -1 && j+1 < numRules) {
                 currentRulePtr = rules[j+1];
            }
            else {
                //printf("BREAK ME FAIL\n");
                break;
            }
        } else if(res) {
            input = res;      
            if(currentRulePtr->onSuccessRuleIndex < numRules && currentRulePtr->onSuccessRuleIndex > -1) {
                currentRulePtr = rules[currentRulePtr->onSuccessRuleIndex];
                j = currentRulePtr->onSuccessRuleIndex;
            } 
            // if no Sn or Fm rule specified, go to next rule if it exists
            else if(currentRulePtr->onSuccessRuleIndex == -1 && j+1 < numRules) {
                currentRulePtr = rules[j+1];
            }
            else {
                //printf("BREAK ME SUCCESS\n");
                break;
            }
        }
    }

    for(int idx = 0; res && idx < strlen(res); idx++) {
        putchar(res[idx]);
    }
    putchar('\n');

    free(input);

    return EXIT_SUCCESS;
}
