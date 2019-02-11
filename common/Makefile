# Makefile for common library
#   Builds and compiles all these utility functions into a library.
#
#Grace Dorgan Feb 2017, based off of code by 
# David Kotz, April 2016, July 2017
# updated by Xia Zhou, July 2016

L = ../libcs50

# object files, and the target library
OBJS = index.o word.o pagedir.o
LIB = common.a
LLIBS = $L/libcs50.a
CFLAGS = -Wall -pedantic -std=c11 -ggdb -I$L
CC = gcc
MAKE = make

# Build the library by archiving object files

$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)

# Dependencies: object files depend on header files
index.o: index.h $L/hashtable.h $L/counters.h word.h $L/file.h pagedir.h
word.o: word.h
pagedir.o: pagedir.h $L/file.h $L/webpage.h

.PHONY: clean sourcelist

# list all the sources and docs in this directory.
sourcelist: Makefile *.md *.c *.h
	@echo $^

# clean up after our compilation
clean:
	rm -f $(LIB) *~ *.o
