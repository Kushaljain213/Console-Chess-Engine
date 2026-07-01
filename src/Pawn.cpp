#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(const Position& position, Color color)
    : Piece(position, color, PieceType::PAWN) {}

std::vector<Position> Pawn::getLegalMoves(const Board& board) const
{
    std::vector<Position> legalMoves;
    int direction = (color == Color::WHITE) ? -1 : 1;
    int startRow = (color == Color::WHITE) ? 6 : 1;

    // One square forward
    Position oneStep(position.row + direction, position.col);
    if (oneStep.isValid() && board.getPiece(oneStep) == nullptr){
        legalMoves.push_back(oneStep);
        // Two squares forward
        Position twoStep(position.row + 2 * direction, position.col);
        if (position.row == startRow &&
            twoStep.isValid() &&
            board.getPiece(twoStep) == nullptr){
            legalMoves.push_back(twoStep);
        }
    }

    // Capture left
    Position leftCapture(position.row + direction, position.col - 1);
    if (leftCapture.isValid()){
        Piece* target = board.getPiece(leftCapture);
        if (target != nullptr && target->getColor() != color){
            legalMoves.push_back(leftCapture);
        }
    }

    // Capture right
    Position rightCapture(position.row + direction, position.col + 1);
    if (rightCapture.isValid()){
        Piece* target = board.getPiece(rightCapture);
        if (target != nullptr && target->getColor() != color){
            legalMoves.push_back(rightCapture);
        }
    }

    return legalMoves;
}