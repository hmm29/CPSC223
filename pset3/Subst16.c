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
#include "/c/cs223/Hwk3/getLine.h"

char* StrStr(const char *str, const char *target) 
{
  if (!*target) return NULL;
  char *p1 = (char*)str;
  while (*p1) {
    char *p1Begin = p1, *p2 = (char*)target;
    while (*p1 && *p2 && (*p1 == *p2 || *p2 == '.')) {  
      p1++;
      p2++;
    }
    if (!*p2)
      return p1Begin;
    p1 = p1Begin + 1;
  }
  return NULL;
}

char *copylastn(char *dest, char *src,int n)
{
    if (!src)
        src = "";
    if (!dest)
        dest = "";

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
    ruleptr->onSuccessRuleIndex = ruleptr->onFailureRuleIndex = ruleptr->filter = -1;

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

   if(ruleptr->filter == -1) {
	ruleptr->filter = 'q';
   }
}

/* 
 * str_replace: finds a substring and replaces all `from` occurrences with `to` according to flag specifier
 */
char *str_replace(char *orig, char *from, char *to, char flag) {
    char *result = NULL; /* the return string */
    char *ins = NULL;    /* the next insert point */
    char *tmp = NULL;    /* temporary */
    char *matched = NULL; /* matched string */
    char *to_cpy = NULL; /* copy of to argument */
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

    // copy to to_cpy
    to_cpy = malloc(strlen(to) + 1);
    strcpy(to_cpy, to);
    to_cpy[strlen(to)] = '\0';

    if(flag == 'g' || flag == 'q') {
        ins = orig;
        for (count = 0; (tmp = StrStr(ins, from)); ++count) {
            if(flag == 'q' && count == 1) {
               break;
            }
            ins = tmp + len_from;

            matched = malloc(3 * sizeof(*matched));
            matched = strncpy(matched, tmp, 2);
            matched[2] = '\0';

            if(strchr(to, '^')) {
                to_cpy = to; // reset to_cpy
                to_cpy = str_replace(to_cpy, "^", matched, 'q');
                len_to = strlen(to_cpy);
            }

            free(matched);
        }

        if(result) free(result);
        tmp = result = malloc(strlen(orig) + (len_to - len_from) * count + 1);

        for(int i = 0; i < strlen(orig) + (len_to - len_from) * count + 1; i++) {
            tmp[i] = '\0';
        }

        if (!result) return NULL;

        while (count--) {
            ins = StrStr(orig, from);
            len_front = ins - orig;
            tmp = strncpy(tmp, orig, len_front) + len_front;
            tmp = strcpy(tmp, to_cpy) + len_to;
            orig += len_front + len_from; // move to next "end of from"

            // printf("result at end is now %s because orig is %s\n", result, orig);
        }
                free(tmp);
    }
    else if(flag == 'r') {
        int len_tmp;

        len_tmp = strlen(orig) + (len_to - len_from);
        tmp = result = malloc(len_tmp+1);
        if (!result) return NULL;

        for(int i = 0; i < len_tmp; i++) {
            tmp[i] = '\0';
        }

        // if(strlen(tmp) < strlen(orig)) {
        //     tmp = realloc(tmp, strlen(orig) + 1);
        // }
            tmp = strcpy(tmp, orig);

        while(StrStr(tmp, from)) { // while there is a leftmost occurrence of from
            ins = StrStr(tmp, from);
            tmp = str_replace(tmp + (ins-tmp), from, to, 'q');
            result = copylastn(result, tmp, strlen(tmp));
            tmp = realloc(tmp, strlen(orig)+1);
        }
        // printf("last result IS awesomely %s.\n", result);
        free(tmp);
    }

    free(to_cpy);

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
	    exit(EXIT_FAILURE);
    }

    if(argc < 4 || (argc-1)%3 > 0) {
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
    char *res = NULL;

    while((input = getLine(stdin)) != NULL) {
            if(input[strlen(input)-1] == '\n') input[strlen(input)-1] = '\0';

            for(int i = 0; i < strlen(input); i++) {
                res = str_replace(input, currentRulePtr->FROM, currentRulePtr->TO, currentRulePtr->filter);
                if (input && res && strcmp(input, res) == 0) {  // if no change
                    if(currentRulePtr->onFailureRuleIndex < numRules && currentRulePtr->onFailureRuleIndex > -1) {
                        if(currentRulePtr->onFailureRuleIndex > -1) {
                            j = currentRulePtr->onFailureRuleIndex;
                            currentRulePtr = rules[j];
                        }
                    } 
                    // if no Sn or Fm rule specified, go to next rule if it exists
                    else if(currentRulePtr->onFailureRuleIndex == -1 && j+1 < numRules) {
                         currentRulePtr = rules[++j];
                    }
                    else {
                        break;
                    }
                } else if(res) {
                    i = 0; // reset iterator
                    if(currentRulePtr->onSuccessRuleIndex < numRules && currentRulePtr->onSuccessRuleIndex > -1) {
                        if(currentRulePtr->onSuccessRuleIndex > -1) {
                            j = currentRulePtr->onSuccessRuleIndex;
                            currentRulePtr = rules[j];
                        }
                        //printf("New rule index success is %d and i is %d\n", j, i);
                    } 
                    // if no Sn or Fm rule specified, go to next rule if it exists
                    else if(currentRulePtr->onSuccessRuleIndex == -1 && j+1 < numRules) {
                        currentRulePtr = rules[++j];
                    }
                    else {
                        //printf("BREAK ME SUCCESS\n");
                        break;
                    }
                    free(input);
                    input = res;
                }
            }

        for(int idx = 0; res && idx < strlen(res); idx++) {
            putchar(res[idx]);
        }
        putchar('\n');

        free(input);
    }

        // free everything
    for(int r = 0; r < numRules; r++) {
        free(rules[r]);
    }

    return EXIT_SUCCESS;
}
