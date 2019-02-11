# Makefile for querier directory
#
# Grace Dorgan Febuary 2018

L = ../libcs50

LIBS =

CFLAGS = -Wall -pedantic -std=gnu11 -ggdb $(FLAGS) -I$L -I../common
CC = gcc
MAKE = make all
LLIBS = $L/libcs50.a ../common/common.a
PROG = querier

all: querier fuzzquery

$(PROG): querier.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o querier
fuzzquery: fuzzquery.o $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o fuzzquery

querier.o: ../common/index.h ../libcs50/counters.h
fuzzquery.o: ../libcs50/memory.h ../libcs50/file.h

.PHONY: clean test

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
test:
	bash test.sh > testing.out
