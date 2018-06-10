#pragma once

#include "ex4.h"

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

template<typename GAME_PIECE>
using PieceData = std::pair<int, GAME_PIECE>;
using std::cout;
using std::endl;
using std::vector;

template<int ROWS , int COLS, typename GAME_PIECE, int NUM_OF_PLAYERS = 2>
class GameBoard {
  private:
    typename std::vector<std::vector<PieceInfo<GAME_PIECE>>> board;

  public:
    class iterator {
        typename vector<PieceInfo<GAME_PIECE>>::iterator rowItr;
        GameBoard *itrBoard;
        int row;
        int col;
        std::tuple<int, int, GAME_PIECE, int> tuple;
      public:
        iterator(typename vector<PieceInfo<GAME_PIECE>>::iterator _rowItr, GameBoard *board, int _row = 0, int _col = 0): rowItr(_rowItr), itrBoard(board), row(_row), col(_col) , tuple(){}

        bool operator!=(iterator other) {
            return row != other.row || col != other.col;// || (rowItr[col]->second != other.rowItr[other.col]->second);
        }

        iterator& operator++() {
            ++rowItr;
            col++;
            if(!(rowItr != (itrBoard->board[row]).end())) {
                row++;
                col = 0;
                if(row < ROWS) {
                    rowItr = itrBoard->board[row].begin();
                } else {
                    rowItr = {};
                }
            }
            return *this;
        }

        const std::tuple<int, int, GAME_PIECE, int>& operator*() {
            if(*rowItr == nullptr){
                cout << "got nullptr in a cell" << endl;
            }
            tuple = std::make_tuple(row, col, (*rowItr)->second, (*rowItr)->first);
            return tuple;
        }
    };

    iterator begin() {
    // TODO: handle board of size zero
        return {this->board[0].begin(), this};
    }

    iterator end() {
        return {this->board[ROWS - 1].end(), this, ROWS, 0};
    }

    GameBoard(): board(0) {
        for (int i = 0; i < ROWS; i++) {
            std::vector<PieceInfo<GAME_PIECE>> line;
            for (int j = 0; j < COLS; j++) {
                PieceInfo<GAME_PIECE> ptr;
                line.push_back(std::move(ptr));
            }
            board.push_back(std::move(line));
        }
    }

    PieceInfo<GAME_PIECE> getPiece(int row, int col) {
        if(board[row][col] != nullptr){
            return std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(board[row][col]->first, board[row][col]->second));
        }
        return nullptr;
    }

    PieceInfo<GAME_PIECE> setPiece(int row, int col, GAME_PIECE piece, int player){
        if(player >= NUM_OF_PLAYERS || player < 0){
            std::cout << "ERROR: incorrect player number" << std::endl;
            return nullptr;
        }
        PieceInfo<GAME_PIECE> prevPiece = std::move(board[row][col]);
        PieceInfo<GAME_PIECE> newPiece = std::make_unique<const std::pair<int, GAME_PIECE>>(std::make_pair(player, piece));
        board[row][col] = std::move(newPiece);
        return std::move(prevPiece);
    }

//    GameBoard should allow iterating over its content in several options:
//  a.
//  b.
//  c.
//  d.

};




