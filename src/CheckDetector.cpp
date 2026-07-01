#include "CheckDetector.h"

#include <vector>

Position CheckDetector::findKing(const Board& board,
                                 Color kingColor)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece* piece = board.getPiece(Position(row, col));

            if (piece != nullptr &&
                piece->getType() == PieceType::KING &&
                piece->getColor() == kingColor)
            {
                return Position(row, col);
            }
        }
    }

    return Position(-1, -1);
}

bool CheckDetector::isSquareAttacked(const Board& board,
                                     const Position& square,
                                     Color attackingColor)
{
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            Piece* piece = board.getPiece(Position(row, col));

            if (piece == nullptr)
                continue;

            if (piece->getColor() != attackingColor)
                continue;

            // ---------------- Pawn ----------------

            if (piece->getType() == PieceType::PAWN)
            {
                int direction =
                    (attackingColor == Color::WHITE) ? -1 : 1;

                Position leftAttack(row + direction, col - 1);
                Position rightAttack(row + direction, col + 1);

                if (leftAttack.isValid() && leftAttack == square)
                    return true;

                if (rightAttack.isValid() && rightAttack == square)
                    return true;

                continue;
            }

            // ------------ Other Pieces ------------

            std::vector<Position> moves =
                piece->getLegalMoves(board);

            for (const Position& move : moves)
            {
                if (move == square)
                    return true;
            }
        }
    }

    return false;
}

bool CheckDetector::isKingInCheck(const Board& board,
                                  Color kingColor)
{
    Position kingPosition = findKing(board, kingColor);

    Color attackingColor =
        (kingColor == Color::WHITE)
            ? Color::BLACK
            : Color::WHITE;

    return isSquareAttacked(board,
                            kingPosition,
                            attackingColor);
}