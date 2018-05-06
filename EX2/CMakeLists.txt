cmake_minimum_required(VERSION 3.10)
project(EX2)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Werror -Wall -Wfatal-errors -Wno-shift-count-overflow -Weffc++ -Wno-non-virtual-dtor -Wno-strict-aliasing -Wno-unused-private-field -pedantic-errors")

include_directories(.)

add_executable(EX2
        Board.h
        FightInfo.h
        JokerChange.h
        Move.h
        PiecePosition.h
        PlayerAlgorithm.h
        Point.h
        BombPiece.cpp
        BombPiece.h
        EndOfGameHandler.cpp
        EndOfGameHandler.h
        FlagPiece.cpp
        FlagPiece.h
        JokerPiece.cpp
        JokerPiece.h
        main.cpp
        Makefile
        Moves.cpp
        Moves.h
        PaperPiece.cpp
        PaperPiece.h
        Parser.cpp
        Parser.h
        Piece.cpp
        Piece.h
        PieceFactory.cpp
        PieceFactory.h
        player1.rps_board
        player1.rps_moves
        player2.rps_board
        player2.rps_moves
        RockPiece.cpp
        RockPiece.h
        RPS.cpp
        RPS.h
        ScissorsPiece.cpp
        ScissorsPiece.h
        MyPoint.cpp
        MyPoint.h
        MyMove.cpp
        MyMove.h MyPiecePosition.cpp MyPiecePosition.h MyJokerChange.cpp MyJokerChange.h GameManager.cpp GameManager.h MyFightInfo.cpp MyFightInfo.h)
