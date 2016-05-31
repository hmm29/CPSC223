CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -g3

HWK3= /c/cs223/Hwk3
HWK4= /c/cs223/Hwk4

all:    Merge16 testQueue Merge16H

# Instructions to make Merge16
Merge16: Merge16.o Queue.o
	${CC} ${CFLAGS} -o $@ $^ ${HWK3}/getLine.o

Merge16.o: ${HWK3}/getLine.h ${HWK4}/Queue.h
Queue.o: ${HWK4}/Queue.h

# Instructions to make testQueue
testQueue: Queue.o
	${CC} ${CFLAGS} -o $@ $^ ${HWK4}/testQueue.o ${HWK3}/getLine.o

testQueue.o: ${HWK3}/getLine.h ${HWK4}/Queue.h

# Instructions to make Merge16H
Merge16H: Merge16.o
	 ${CC} ${CFLAGS} -o $@ $^ ${HWK3}/getLine.o ${HWK4}/Queue.o

Merge16H.o: ${HWK3}/getLine.h ${HWK4}/Queue.h

# Delete executables and objects
clean:
	/bin/rm -f Merge16 testQueue Merge16H *.o







