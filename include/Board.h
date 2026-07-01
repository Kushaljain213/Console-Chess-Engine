#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"
#include "Position.h"
#include "Move.h"

class Board{
private:
    Piece* board[8][8];
    void printHorizontalBorder() const;
    std::string getPieceSymbol(const Piece* piece) const;

public:
    Board();
    ~Board();
    void setupBoard();
    void makeMove(const Move& move);
    void promotePawn(const Position& position, PieceType newType);
    void undoMove(const Move& move);
    Piece* getPiece(const Position& position) const;
    void placePiece(Piece* piece);
    void removePiece(const Position& position);    
    void movePiece(const Position& from, const Position& to);
    void printBoard() const;   
};

#endif