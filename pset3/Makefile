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
Hwk3=/c/cs223/Hwk3

# Rule to build executable from object files
Subst16: Subst16.o Hwk3/getLine.o
	${CC} ${CFLAGS} -o Subst16 Subst16.o Hwk3/getLine.o

# Rule to generate object files
%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

# Rule to clean up directory
clean:
	rm -f *.o Subst16
