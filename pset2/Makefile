#
#       Created by Harrison Miller
#       Course CS223, Spring 2016
#       Problem Set 2
#
#       Makefile

# Specify compiler
CC=gcc

# Specify flags and other macros
CFLAGS=-std=c99 -g3 -Wall -pedantic
HWK=/c/cs223/Hwk2

# Rule to build executable from object files
Psched: Psched.o util.o
	${CC} ${CFLAGS} -o Psched Psched.o util.o

# Rule to generate object files
%.o: %.c
	${CC} ${CFLAGS} -c -o $@ $<

# Rule to clean up directory
clean:
	rm -f *.o Psched
