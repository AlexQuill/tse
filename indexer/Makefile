# Makefile for indexer directory
#
# Grace Dorgan Febuary 2018

L = ../libcs50

LIBS =

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I../common
CC = gcc
MAKE = make all
LLIBS = $L/libcs50.a ../common/common.a

all: indexer indextest

indexer: indexer.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o indexer

indextest: indextest.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o indextest

indexer.o: ../common/index.h
indextest.o: ../common/index.h

.PHONY: clean test

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
test:
	bash test.sh > testing.out
