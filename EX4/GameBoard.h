#pragma once

#include "ex4.h"

template<typename GAME_PIECE>
using PieceInfo = std::unique_ptr<const std::pair<int, GAME_PIECE>>;

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
        int player;
        GAME_PIECE *piece;
        std::tuple<int, int, GAME_PIECE, int> tuple;
      public:
        iterator(typename vector<PieceInfo<GAME_PIECE>>::iterator _rowItr, GameBoard *board, int _row = 0, int _col = 0, int player_ = -1, GAME_PIECE *piece_ = nullptr): rowItr(_rowItr), itrBoard(board), row(_row), col(_col), player(player_), piece(piece_), tuple() {}

        bool operator!=(iterator other) {
            return row != other.row || col != other.col;;
        }

        iterator& operator++() {
            if (row == -1) {
                row = 0;
                col = 0;
                rowItr = itrBoard->board[row].begin();
            } else {
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
            }
            if (rowItr != (itrBoard->board[row]).end()) {
                if ((player != -1) && (piece == nullptr) && ((*rowItr)->first != player)) {
                    return ++(*this);
                } else if ((player == -1) && (piece != nullptr) && ((*rowItr)->second != *piece)) {
                    return ++(*this);
                } else if ((player != -1) && (piece != nullptr) && (((*rowItr)->first != player) || ((*rowItr)->second != *piece))) {
                    return ++(*this);
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

//  b.
        class PiecesOfPlayer{
            int playerNum;
            GameBoard *playerBoard;
        public:
            PiecesOfPlayer(int playerNum_, GameBoard *board_): playerNum(playerNum_), playerBoard(board_){}

            iterator begin(){
                return ++(iterator(this->playerBoard->board[0].begin(), this->playerBoard, -1, 0, playerNum));
            }

            iterator end(){
                return iterator(this->playerBoard->board[ROWS - 1].end(), this->playerBoard, ROWS, 0);

            }
        };
        PiecesOfPlayer allPiecesOfPlayer(int playerNum){
            return PiecesOfPlayer(playerNum, this);
        }

//  c.
    class OccureneceOfPiece{
        GAME_PIECE piece;
        GameBoard *playerBoard;
      public:
        OccureneceOfPiece(GAME_PIECE piece_, GameBoard *board_): piece(piece_), playerBoard(board_){}

        iterator begin(){
            return ++(iterator(this->playerBoard->board[0].begin(), this->playerBoard, -1, 0, -1, &piece));
        }

        iterator end(){
            return iterator(this->playerBoard->board[ROWS - 1].end(), this->playerBoard, ROWS, 0);
        }
    };
    OccureneceOfPiece allOccureneceOfPiece(GAME_PIECE piece){
        return OccureneceOfPiece(piece, this);
    }

//  d.
    class OccureneceOfPieceForPlayer{
        GAME_PIECE piece;
        int playerNum;
        GameBoard *playerBoard;
      public:
        OccureneceOfPieceForPlayer(GAME_PIECE piece_, int playerNum_, GameBoard *board_): piece(piece_), playerNum(playerNum_), playerBoard(board_){}

        iterator begin(){
            return ++(iterator(this->playerBoard->board[0].begin(), this->playerBoard, -1, 0, playerNum, &piece));
        }

        iterator end(){
            return iterator(this->playerBoard->board[ROWS - 1].end(), this->playerBoard, ROWS, 0);
        }
    };
    OccureneceOfPieceForPlayer allOccureneceOfPieceForPlayer(GAME_PIECE piece, int playerNum_){
        return OccureneceOfPieceForPlayer(piece, playerNum_, this);
    }
};




