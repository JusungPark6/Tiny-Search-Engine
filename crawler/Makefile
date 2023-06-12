# Jusung Park
# CS50 Winter 2023
# Makefile for the crawler module
#

OBJS = crawler.o ../common/pagedir.o
LIBS = 
L = ../libcs50
LLIBS = $L/libcs50-given.a

# uncomment the following to turn on verbose memory logging
TESTING=-DMEMTEST

CC = gcc
CFLAGS = -Wall -pedantic -std=c11 -ggdb $(TESTING) -I$L -I../common
MAKE = make

# for memory-leak tests
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all

crawler: $(OBJS) $(LLIBS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

.PHONY: test valgrind clean

# expects a file `test.names` to exist; it can contain any text.
test: crawler
	bash -v testing.sh

# # expects a file `test.names` to exist; it can contain any text.
valgrind: crawler
	$(VALGRIND) ./$< $(TESTINGINPUT)

clean:
	rm -rf *.dSYM  # MacOS debugger info
	rm -f *~ *.o
	rm -f crawler
	rm -f core
