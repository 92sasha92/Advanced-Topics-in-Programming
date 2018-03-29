cmake_minimum_required(VERSION 3.8)
project(EX)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp BombPiece.cpp BombPiece.h FlagPiece.cpp FlagPiece.h JokerPiece.cpp JokerPiece.h PaperPiece.cpp PaperPiece.h Piece.cpp Piece.h PieceFactory.cpp PieceFactory.h RockPiece.cpp RockPiece.h RPS.cpp RPS.h ScissorsPiece.cpp ScissorsPiece.h)
add_executable(EX ${SOURCE_FILES})