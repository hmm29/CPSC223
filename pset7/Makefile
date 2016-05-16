#
#       Created by Harrison Miller
#       Course CS223, Spring 2016
#       Problem Set 7
#
#       Makefile

# Specify compiler
CC=gcc

# Specify flags and other macros
CFLAGS=-std=c99 -g3 -Wall -pedantic
HWK3 = /c/cs223/Hwk3/

# Rule to build executable from object files
Boggle: Boggle.o ${HWK3}getLine.o
	$(CC) $(CFLAGS) -o Boggle Boggle.o ${HWK3}getLine.o

# Rule to generate object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule for object file header dependency
Boggle.o ${HWK3}getLine.o: ${HWK3}getLine.h

# Rule to clean up directory
clean:
	rm -f *.o Boggle
