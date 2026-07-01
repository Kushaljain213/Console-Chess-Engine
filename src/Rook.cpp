#include "Rook.h"
#include "Board.h"

Rook::Rook(const Position& position, Color color)
    : Piece(position, color, PieceType::ROOK) {}

std::vector<Position> Rook::getLegalMoves(const Board& board) const
{
    std::vector<Position> legalMoves;

    const int rowDirection[4] = {-1, 1, 0, 0};
    const int colDirection[4] = {0, 0, -1, 1};

    for (int dir = 0; dir < 4; dir++)
    {
        int newRow = position.row;
        int newCol = position.col;

        while (true)
        {
            newRow += rowDirection[dir];
            newCol += colDirection[dir];

            Position newPosition(newRow, newCol);

            if (!newPosition.isValid())
                break;

            Piece* target = board.getPiece(newPosition);

            if (target == nullptr)
            {
                legalMoves.push_back(newPosition);
            }
            else
            {
                if (target->getColor() != color)
                {
                    legalMoves.push_back(newPosition);
                }
                break;
            }
        }
    }

    return legalMoves;
}