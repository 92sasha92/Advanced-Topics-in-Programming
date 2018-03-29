cmake_minimum_required(VERSION 3.8)
project(EX1vs2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        ConsoleApplication1/ConsoleApplication1/BombPiece.cpp
        ConsoleApplication1/ConsoleApplication1/BombPiece.h
        ConsoleApplication1/ConsoleApplication1/main.cpp
        ConsoleApplication1/ConsoleApplication1/FlagPiece.cpp
        ConsoleApplication1/ConsoleApplication1/FlagPiece.h
        ConsoleApplication1/ConsoleApplication1/JokerPiece.cpp
        ConsoleApplication1/ConsoleApplication1/JokerPiece.h
        ConsoleApplication1/ConsoleApplication1/PaperPiece.cpp
        ConsoleApplication1/ConsoleApplication1/PaperPiece.h
        ConsoleApplication1/ConsoleApplication1/Piece.cpp
        ConsoleApplication1/ConsoleApplication1/Piece.h
        ConsoleApplication1/ConsoleApplication1/PieceFactory.cpp
        ConsoleApplication1/ConsoleApplication1/PieceFactory.h
        ConsoleApplication1/ConsoleApplication1/RockPiece.cpp
        ConsoleApplication1/ConsoleApplication1/RockPiece.h
        ConsoleApplication1/ConsoleApplication1/RPS.cpp
        ConsoleApplication1/ConsoleApplication1/RPS.h
        ConsoleApplication1/ConsoleApplication1/ScissorsPiece.cpp
        ConsoleApplication1/ConsoleApplication1/ScissorsPiece.h
        ConsoleApplication1/ConsoleApplication1/stdafx.cpp
        ConsoleApplication1/ConsoleApplication1/stdafx.h
        ConsoleApplication1/ConsoleApplication1/targetver.h)

add_executable(EX1vs2 ${SOURCE_FILES})