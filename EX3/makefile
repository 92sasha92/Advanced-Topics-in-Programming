CC=g++-5.3.0
AR=ar
RM=rm
IDIR =include
LIBS = -ldl

UNAME := $(shell uname -s)

COMP_FLAG=-std=c++14 -Wall -Wextra -Werror -pedantic-errors -Wfatal-errors -Wno-shift-count-overflow -Weffc++ -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-unused-private-field -fPIC
LDFLAGS = -pthread -ldl
OBJS = TournamentManager.o AlgorithmRegistration.o BombPiece.o RockPiece.o ScissorsPiece.o FlagPiece.o JokerPiece.o PaperPiece.o RPS.o main.o Piece.o PieceFactory.o Parser.o EndOfGameHandler.o MyMove.o MyPoint.o MyPiecePosition.o  MyJokerChange.o GameManager.o FileAlgorithm.o MyBoard.o MyFightInfo.o BattleInfo.o
EXEC = ex3
HEADERFILESSO = AlgorithmRegistration.h Board.h Point.h MyBoard.h MyPoint.h FightInfo.h JokerChange.h Move.h PiecePosition.h MyFightInfo.h MyJokerChange.h MyMove.h MyPiecePosition.h RPS.h PieceFactory.h BombPiece.h RockPiece.h ScissorsPiece.h FlagPiece.h JokerPiece.h PaperPiece.h Piece.h EndOfGameHandler.h
CPPFSO = MyBoard.cpp MyPoint.cpp MyFightInfo.cpp MyJokerChange.cpp MyMove.cpp MyPiecePosition.cpp RPS.cpp PieceFactory.cpp BombPiece.cpp RockPiece.cpp ScissorsPiece.cpp FlagPiece.cpp JokerPiece.cpp PaperPiece.cpp Piece.cpp EndOfGameHandler.cpp
rps_tournament: $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) -ldl -pthread -lpthread -rdynamic 
	
rps_lib: RSPPlayer_204251599.cpp RSPPlayer_204251599.h $(HEADERFILESSO)
	$(CC) $(COMP_FLAG) RSPPlayer_204251599.cpp $(CPPFSO) -shared -fPIC -rdynamic -o RSPPlayer_204251599.so
	
rps_lib2: RSPPlayer_323239566.cpp RSPPlayer_323239566.h $(HEADERFILESSO)
	$(CC) $(COMP_FLAG) RSPPlayer_323239566.cpp $(CPPFSO) -shared -fPIC -rdynamic -o RSPPlayer_323239566.so
	
rps_lib3: RSPPlayer_123.cpp $(HEADERFILESSO)
	$(CC) $(COMP_FLAG) RSPPlayer_123.cpp $(CPPFSO) -shared -fPIC -rdynamic -o RSPPlayer_123.so
	
rps_lib4: RSPPlayer_111.cpp $(HEADERFILESSO)
	$(CC) $(COMP_FLAG) RSPPlayer_111.cpp $(CPPFSO) -shared -fPIC -rdynamic -o RSPPlayer_111.so

rps_lib5: RSPPlayer_222.cpp $(HEADERFILESSO)
	$(CC) $(COMP_FLAG) RSPPlayer_222.cpp $(CPPFSO) -shared -fPIC -rdynamic -o RSPPlayer_222.so

all:	$(EXEC)
$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
TournamentManager.o: TournamentManager.h TournamentManager.cpp PlayerAlgorithm.h
	$(CC) $(COMP_FLAG) -c $*.cpp
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
main.o: main.cpp RPS.h MyMove.h GameManager.h TournamentManager.h
	$(CC) $(COMP_FLAG) -rdynamic -c $*.cpp $(LIBS)
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
FileAlgorithm.o: FileAlgorithm.h FileAlgorithm.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
MyBoard.o: MyBoard.h MyBoard.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
MyFightInfo.o: MyFightInfo.h MyFightInfo.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
RSPPlayer_204251599.o: PlayerAlgorithm.h RSPPlayer_204251599.h RSPPlayer_204251599.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp -fPIC
BattleInfo.o: BattleInfo.h BattleInfo.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp
AlgorithmRegistration.o: AlgorithmRegistration.h AlgorithmRegistration.cpp
	$(CC) $(COMP_FLAG) -c $*.cpp

clean:
	rm -f *.o $(EXEC)
clean_so: 
	rm -f *.so
