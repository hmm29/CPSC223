#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define ungetchar(c) ungetc(c,stdin)    // Unread char read from stdin
#define IS_NOT_COUNTABLE_LINE (0)
#define IS_COUNTABLE_LINE (1)

int main() {
    
    int c, numLines, state;
    bool isCharConstant, isSingleLineComment, isMultiLineComment, isString;

    numLines = 0;
    state = IS_NOT_COUNTABLE_LINE;
    isCharConstant = false;
    isSingleLineComment = false;
    isMultiLineComment = false;
    isString = false;

    while((c = getchar()) != EOF) {
        // Error checking, only accept valid C characters
        if(c > 255 || c < -1) exit(1);

        // Handle line splicing and comments
        if(c == '\\') {
	    putchar(c);
            c = getchar();
            if(c == '\n') {
                putchar(c);
            }
            else if (c == '\"' || c == '\'') {
		putchar(c);	
	    }
            else {
                ungetchar(c);
            }
        }

	// Handle comments
	else if (c == '/') {
	   putchar(c);
 	   c = getchar();
	   if((c == '*') && !isMultiLineComment) {
	   	putchar(c);
		isMultiLineComment = true;
	   }
	   else if((c == '/') && !isSingleLineComment) {
 		putchar(c);
		isSingleLineComment = true;
	   }
	   else {
		ungetchar(c);
	   }
	}

        // Newline character logic
        // Handle line-counting logic depending on state of machine
        else if(c == '\n') {
            if((state == IS_COUNTABLE_LINE) && !isString && !isCharConstant && !isMultiLineComment) {
                printf(" //%d\n", ++numLines);
                state = IS_NOT_COUNTABLE_LINE;
		if(isSingleLineComment) {
			isSingleLineComment = false;
		}
            }
            else {
                putchar(c);
            }
        }

        // Handle end of multi-line comment
        else if(c == '*') {
	    putchar(c);
            c = getchar();
            if(c == '/' && isMultiLineComment) {
		putchar(c);
                isMultiLineComment = false;
            } else {
                ungetchar(c);
            }
        }

        // Handle beginning char constants
        else if (c == '\'' && !isCharConstant && !isMultiLineComment && !isSingleLineComment && !isString) {
            	putchar(c);
		isCharConstant = true;
        }

        // Handle end char constants
        else if (c == '\'' && isCharConstant && !isMultiLineComment && !isSingleLineComment && !isString) {
           	putchar(c);
		isCharConstant = false;
		state = IS_COUNTABLE_LINE;
        }

        // Handle beginning string
        else if (c == '\"' && !isString && !isMultiLineComment && !isSingleLineComment && !isCharConstant) {
            	putchar(c);
		isString = true;
        }

        // Handle end string
        else if (c == '\"' && isString && !isMultiLineComment && !isSingleLineComment && !isCharConstant) {
            	putchar(c);
		isString = false;
		state = IS_COUNTABLE_LINE;
        }
	// Handle chars outside comments
        else if (!isspace(c) && c != '{' && c != '(' && c != '}' && c != ')' && !isMultiLineComment && !isSingleLineComment) {
                // Ignore 'else' keyword
                if(c == 'e') {
                    putchar(c);
                    c = getchar();
                    if(c == 'l' || c == '\n') {
                        putchar(c);
                        c = getchar();
                        if(c == 's' || c == '\n') {
                            putchar(c);
                            c = getchar();
                            if(c == 'e' || c == '\n') {
                                putchar(c);
                            } else {
                                ungetchar(c);
                                state = IS_COUNTABLE_LINE;
                            }
                        } else {
                            ungetchar(c);
                            state = IS_COUNTABLE_LINE;
                        }
                    } else {
                        ungetchar(c);
                        state = IS_COUNTABLE_LINE;
                    }

                } else {
                    	putchar(c);
			state = IS_COUNTABLE_LINE;
                }
            } 
	// Print chars in comments
        else {
       	   putchar(c);
	 }

    }

    return EXIT_SUCCESS;
}

