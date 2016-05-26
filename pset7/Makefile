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

# Rule to build executable from object files
Boggle: Boggle.o
	$(CC) $(CFLAGS) -o Boggle Boggle.o

# Rule to generate object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to clean up directory
clean:
	rm -f *.o Boggle
