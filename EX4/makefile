CC=g++-5.3.0
AR=ar
RM=rm
IDIR =include

UNAME := $(shell uname -s)

COMP_FLAG=-std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG
OBJS = main.o
EXEC = ex4


all:	$(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)
main.o: main.cpp unit_test_util.h ex4_header.h GameBoard.h
	$(CC) $(COMP_FLAG) -c $*.cpp

clean:
	rm -f *.o $(EXEC)
