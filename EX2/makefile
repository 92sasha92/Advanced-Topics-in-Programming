CC=g++-5.3.0
AR=ar
RM=rm
IDIR =include

UNAME := $(shell uname -s)

COMP_FLAG=-std=c++14 -Wall -Wextra -Werror -pedantic-errors -Wfatal-errors -Wno-shift-count-overflow -Weffc++ -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-unused-private-field

OBJS = BombPiece.o RockPiece.o ScissorsPiece.o FlagPiece.o JokerPiece.o PaperPiece.o RPS.o main.o Piece.o PieceFactory.o Parser.o EndOfGameHandler.o MyMove.o MyPoint.o MyPiecePosition.o  MyJokerChange.o GameManager.o AutoAlgorithm.o FileAlgorithm.o MyBoard.o MyFightInfo.o
EXEC = ex2

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
main.o: main.cpp RPS.h MyMove.h GameManager.h AutoAlgorithm.h
	$(CC) $(COMP_FLAG) -c $*.cpp
Piece.o: Piece.h Piece.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
Parser.o: Parser.h Parser.cpp RPS.h
	$(CC) $(COMP_FLAG) -c $*.cpp
EndOfGameHandler.o: EndOfGameHandler.h EndOfGameHandler.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
PieceFactory.o: PieceFactory.h PieceFactory.cpp Piece.h BombPiece.h RockPiece.h ScissorsPiece.h FlagPiece.h JokerPiece.h PaperPiece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
MyMove.o: MyMove.h MyMove.cpp MyPoint.h MyPoint.h Move.h
	$(CC) $(COMP_FLAG) -c $*.cpp
MyPoint.o: MyPoint.h MyPoint.cpp Point.h
	$(CC) $(COMP_FLAG) -c $*.cpp
MyPiecePosition.o: MyPiecePosition.h MyPiecePosition.cpp Piece.h MyPoint.h PiecePosition.h
	$(CC) $(COMP_FLAG) -c $*.cpp
MyJokerChange.o: MyJokerChange.h MyJokerChange.cpp JokerChange.h MyPoint.h Piece.h
	$(CC) $(COMP_FLAG) -c $*.cpp
GameManager.o: GameManager.h GameManager.cpp MyPoint.h
	$(CC) $(COMP_FLAG) -c $*.cpp
AutoAlgorithm.o: AutoAlgorithm.h AutoAlgorithm.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
FileAlgorithm.o: FileAlgorithm.h FileAlgorithm.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
MyBoard.o: MyBoard.h MyBoard.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
MyFightInfo.o: MyFightInfo.h MyFightInfo.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
clean:
	rm -f *.o $(EXEC) $(UNIT_TESTS)

