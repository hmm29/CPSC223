/*
 * File: Subst16.h
 * Programmer: Harrison Miller
 * Description: this file contains function prototypes for the functions defined and called in Subst16.c.
 */

#ifndef SUBST16_H
#define SUBST16_H

#include <stdbool.h>

typedef struct rule {
 	char *FROM;
	char *TO;
	char filter;
	int onSuccessRuleIndex;
	int onFailureRuleIndex;
	bool succeeded;
	bool failed;
} Rule;

typedef struct rule *Ruleptr;

char* StrStr(const char *str, const char *target);
char *copylastn(char *dest,char *src,int n);
void parseFlags(char *flags, Ruleptr ruleptr);
char *inputString(FILE* fp, size_t size);
char *str_replace(char *orig, char *from, char *to, char flag);

#endif
/* end SUBST16_H */
