cmake_minimum_required(VERSION 3.8)
project(EX1_v2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp RPS.cpp RPS.h PieceFactory.cpp PieceFactory.h Piece.cpp Piece.h RockPiece.cpp RockPiece.h PaperPiece.cpp PaperPiece.h ScissorsPiece.cpp ScissorsPiece.h BombPiece.cpp BombPiece.h JokerPiece.cpp JokerPiece.h FlagPiece.cpp FlagPiece.h Parser.cpp Parser.h Moves.cpp Moves.h EndOfGameHandler.cpp EndOfGameHandler.h)
add_executable(EX1_v2 ${SOURCE_FILES} RPS.cpp RPS.h PieceFactory.cpp PieceFactory.h Piece.cpp Piece.h RockPiece.cpp RockPiece.h PaperPiece.cpp PaperPiece.h ScissorsPiece.cpp ScissorsPiece.h BombPiece.cpp BombPiece.h JokerPiece.cpp JokerPiece.h FlagPiece.cpp FlagPiece.h Parser.cpp Parser.h Moves.cpp Moves.h EndOfGameHandler.cpp EndOfGameHandler.h)