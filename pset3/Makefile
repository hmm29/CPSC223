#
#       Created by Harrison Miller
#       Course CS223, Spring 2016
#       Problem Set 3
#
#       Makefile

# Specify compiler
CC=gcc

# Specify flags and other macros
CFLAGS=-std=c99 -g3 -Wall -pedantic

# Rule to build executable from object files
Subst16: Subst16.o /c/cs223/Hwk3/getLine.o
         ${CC} ${CFLAGS} -o Subst16 Subst16.o "Hwk3/getLine.o"

# Rule to generate object files
Subst16.o: Subst16.c
        ${CC} ${CFLAGS} -o Subst16.c "Hwk3/getLine.h"

# Rule to clean up directory
clean:
	rm -f *.o Subst16