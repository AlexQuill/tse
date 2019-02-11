# Makefile for crawler
#
# Grace Dorgan Jan 2018

L = ../libcs50

PROG = crawler
OBJS = crawler.o ../libcs50/webpage.o ../libcs50/bag.o ../libcs50/hashtable.o 
LIBS =

# uncomment the following to turn on verbose memory logging
# TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I../common
CC = gcc
MAKE = make
LLIBS = $L/libcs50.a ../common/common.a

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ $(LLIBS) $(LIBS) -o $@

crawler.o: ../libcs50/bag.h ../libcs50/hashtable.h ../libcs50/webpage.h ../common/pagedir.h
bag.o: ../libcs50/bag.h
hashtable.o: ../libcs50/hashtable.h
webpage.o: ../libcs50/webpage.h

.PHONY: clean test

clean:
	rm -f *~ *.o *.dSYM
	rm -f $(PROG)
test:
	bash test.sh

