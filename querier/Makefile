# Makefile for querier.c
# CS50 Palmer
# Kevin Lin 
# October 22, 2021

PROG1 = querier
PROG2 = indextest
OBJS1 = querier.o query.o ../common/word.o ../common/index.o
LIBS = ../libcs50/libcs50-given.a -lm

# uncomment the following to turn on verbose memory logging
#TESTING=-DMEMTEST

CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I../libcs50 -I../common
CC = gcc
MAKE = make
# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

L = ../libcs50
C = ../common

all: querier

$(PROG1): $(OBJS1)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: test valgrind clean

test: querier
	bash -v testing.sh

valgrind:
	$(VALGRIND) ./querier ../indexer/testDir/letters-10 testIndex.index

run:
	./querier ../indexer/testDir/letters-10 testIndex.index

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f core
