#include "Board.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
#include "Move.h"
#include <windows.h>
#include <string>
#include <iostream>


Board::Board(){
    for(int row = 0 ; row < 8 ; row++){
        for(int col = 0 ; col < 8 ; col++){
            board[row][col] = nullptr;
        }
    }
    setupBoard();
}
Board::~Board(){
    for(int row = 0 ; row < 8 ; row++){
        for(int col = 0 ; col < 8 ; col++){
            delete board[row][col];
            board[row][col] = nullptr;
        }
    }
}

Piece* Board::getPiece(const Position& position) const {
    return board[position.row][position.col];
}

void Board::setupBoard(){
    //  My board looks like this
    // 0  r n b q k b n r   (Black)
    // 1  p p p p p p p p   (Black)
    // 2  . . . . . . . .
    // 3  . . . . . . . .
    // 4  . . . . . . . .
    // 5  . . . . . . . .
    // 6  P P P P P P P P   (White)
    // 7  R N B Q K B N R   (White)

    //White Pawns
    for(int col = 0 ; col < 8 ; col++){
        placePiece(new Pawn(Position(6,col),Color::WHITE));
    }
    //Black Pawns
    for(int col = 0 ; col < 8 ; col++){
        placePiece(new Pawn(Position(1,col),Color::BLACK));
    }

    // All remaining White Pieces
    placePiece(new Rook(Position(7, 0), Color::WHITE));
    placePiece(new Knight(Position(7, 1), Color::WHITE));
    placePiece(new Bishop(Position(7, 2), Color::WHITE));
    placePiece(new Queen(Position(7, 3), Color::WHITE));
    placePiece(new King(Position(7, 4), Color::WHITE));
    placePiece(new Bishop(Position(7, 5), Color::WHITE));
    placePiece(new Knight(Position(7, 6), Color::WHITE));
    placePiece(new Rook(Position(7, 7), Color::WHITE));

    //All remaining Black Pieces
    placePiece(new Rook(Position(0, 0), Color::BLACK));
    placePiece(new Knight(Position(0, 1), Color::BLACK));
    placePiece(new Bishop(Position(0, 2), Color::BLACK));
    placePiece(new Queen(Position(0, 3), Color::BLACK));
    placePiece(new King(Position(0, 4), Color::BLACK));
    placePiece(new Bishop(Position(0, 5), Color::BLACK));
    placePiece(new Knight(Position(0, 6), Color::BLACK));
    placePiece(new Rook(Position(0, 7), Color::BLACK));
}

void Board::placePiece(Piece* piece){
    Position position = piece->getPosition();
    board[position.row][position.col] = piece;
}
void Board::removePiece(const Position& position){
    board[position.row][position.col] = nullptr;
}
void Board::makeMove(const Move& move){
    Piece* movedPiece = move.getMovedPiece();

    Position from = move.getFrom();
    Position to = move.getTo();

    board[from.row][from.col] = nullptr;

    board[to.row][to.col] = movedPiece;

    movedPiece->setPosition(to);
    movedPiece->setHasMoved(true);
    if (movedPiece->getType() == PieceType::KING)
    {
        int diff = to.col - from.col;

        // Kingside Castling
        if (diff == 2)
        {
            Piece* rook = board[from.row][7];

            board[from.row][5] = rook;
            board[from.row][7] = nullptr;

            rook->setPosition(Position(from.row, 5));
            rook->setHasMoved(true);
        }

        // Queenside Castling
        else if (diff == -2)
        {
            Piece* rook = board[from.row][0];

            board[from.row][3] = rook;
            board[from.row][0] = nullptr;

            rook->setPosition(Position(from.row, 3));
            rook->setHasMoved(true);
        }
    }
}
void Board::promotePawn(const Position& position, PieceType newType){
    Piece* pawn = getPiece(position);

    if (pawn == nullptr || pawn->getType() != PieceType::PAWN)
        return;

    Color color = pawn->getColor();

    delete pawn;

    switch (newType)
    {
        case PieceType::QUEEN:
            board[position.row][position.col] = new Queen(position, color);
            break;

        case PieceType::ROOK:
            board[position.row][position.col] = new Rook(position, color);
            break;

        case PieceType::BISHOP:
            board[position.row][position.col] = new Bishop(position, color);
            break;

        case PieceType::KNIGHT:
            board[position.row][position.col] = new Knight(position, color);
            break;

        default:
            board[position.row][position.col] = new Queen(position, color);
            break;
    }
}
void Board::movePiece(const Position& from, const Position& to){
    Piece* movedPiece = getPiece(from);
    Piece* capturedPiece = getPiece(to);

    Move move(from, to, movedPiece, capturedPiece);

    makeMove(move);
}
void Board::undoMove(const Move& move)
{
    
    Piece* movedPiece = move.getMovedPiece();
    Piece* capturedPiece = move.getCapturedPiece();

    Position from = move.getFrom();
    Position to = move.getTo();

    // Undo castling
    if (movedPiece->getType() == PieceType::KING)
    {
        int diff = to.col - from.col;

        // Kingside
        if (diff == 2)
        {
            Piece* rook = board[from.row][5];

            board[from.row][7] = rook;
            board[from.row][5] = nullptr;

            if (rook != nullptr)
            {
                rook->setPosition(Position(from.row, 7));
                rook->setHasMoved(move.getRookHadMoved());
            }
        }
        // Queenside
        else if (diff == -2)
        {
            Piece* rook = board[from.row][3];

            board[from.row][0] = rook;
            board[from.row][3] = nullptr;

            if (rook != nullptr)
            {
                rook->setPosition(Position(from.row, 0));
                rook->setHasMoved(move.getRookHadMoved());
            }
        }
    }

    board[from.row][from.col] = movedPiece;
    movedPiece->setPosition(from);

    board[to.row][to.col] = capturedPiece;

    if (capturedPiece != nullptr)
    {
        capturedPiece->setPosition(to);
    }

    movedPiece->setHasMoved(move.getMovedPieceHadMoved());
}
void Board::printHorizontalBorder() const{
    std::cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+\n";
}
std::string Board::getPieceSymbol(const Piece* piece) const
{
    if(piece->getColor() == Color::WHITE)
    {
        switch(piece->getType())
        {
            case PieceType::KING:   return "♔";
            case PieceType::QUEEN:  return "♕";
            case PieceType::ROOK:   return "♖";
            case PieceType::BISHOP: return "♗";
            case PieceType::KNIGHT: return "♘";
            case PieceType::PAWN:   return "♙";
        }
    }
    else
    {
        switch(piece->getType())
        {
            case PieceType::KING:   return "♚";
            case PieceType::QUEEN:  return "♛";
            case PieceType::ROOK:   return "♜";
            case PieceType::BISHOP: return "♝";
            case PieceType::KNIGHT: return "♞";
            case PieceType::PAWN:   return "♟";
        }
    }

    return " ";
}
void Board::printBoard() const{
    std::cout << "\n";
    std::cout << "=========================================\n";
    std::cout << "         CONSOLE CHESS ENGINE\n";
    std::cout << "=========================================\n\n";
    std::cout << "     a     b     c     d     e     f     g     h\n";
    printHorizontalBorder();
    for(int row = 0 ; row < 8 ; row++){
        std::cout << 8-row << " ";
        for(int col = 0 ; col < 8 ; col++){
            if(board[row][col] == nullptr){
                std::cout << "|     ";
                continue;
            }
            Piece* piece = board[row][col];
            std::string symbol = getPieceSymbol(piece);
            std::cout << "|  " << symbol << "  ";
        } 
        std::cout << "|\n";
        printHorizontalBorder();
    }
}