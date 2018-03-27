CC=g++
AR=ar
RM=rm
IDIR =include

UNAME := $(shell uname -s)

COMP_FLAG=-std=c++11 -Werror -Wall -Wfatal-errors -Wno-shift-count-overflow -Weffc++ -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-unused-private-field

OBJS = BombPiece.o RockPiece.o ScissorsPiece.o FlagPiece.o JokerPiece.o PaperPiece.o RPS.o main.o Piece.o PieceFactory.o
EXEC = rps

all:	$(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
BombPiece.o: BombPiece.h BombPiece.cpp Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
RockPiece.o: RockPiece.h RockPiece.cpp Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
ScissorsPiece.o: ScissorsPiece.h ScissorsPiece.cpp Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
FlagPiece.o: FlagPiece.h FlagPiece.cpp Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
JokerPiece.o: JokerPiece.h JokerPiece.cpp Piece.h PieceFactory.h
	$(CC) $(COMP_FLAG) -c $*.cpp
PaperPiece.o: PaperPiece.h PaperPiece.cpp Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
RPS.o: RPS.h RPS.cpp Piece.h PieceFactory.h
	$(CC) $(COMP_FLAG) -c $*.cpp
main.o: main.cpp RPS.h
	$(CC) $(COMP_FLAG) -c $*.cpp
Piece.o: Piece.h Piece.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
PieceFactory.o: PieceFactory.h PieceFactory.cpp Piece.h BombPiece.h RockPiece.h ScissorsPiece.h FlagPiece.h JokerPiece.h PaperPiece.h
	$(CC) $(COMP_FLAG) -c $*.cpp

clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)

