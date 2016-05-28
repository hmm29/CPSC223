CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

HWK3= /c/cs223/Hwk3
HWK4= /c/cs223/Hwk4

all:    Merge16

Merge16: Merge16.o Queue.o
	${CC} ${CFLAGS} -o $@ $^ ${HWK3}/getLine.o

Merge16.o: ${HWK3}/getLine.h ${HWK4}/Queue.h

Queue.o: ${HWK4}/Queue.h

clean:
	rm -f Merge16 *.o