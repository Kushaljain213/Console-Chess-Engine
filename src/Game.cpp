#include "Game.h"
#include "CheckDetector.h"
#include <iostream>
#include <string>
#include <vector>

Game::Game()
    : whitePlayer("Player 1", Color::WHITE),
      blackPlayer("Player 2", Color::BLACK),
      gameState(GameState::RUNNING),
      currentTurn(Color::WHITE)
       {}

Position Game::getPositionFromUser() const
{
    std::string input;

    while (true)
    {
        std::cin >> input;

        if (input.length() == 2 &&
            input[0] >= 'a' && input[0] <= 'h' &&
            input[1] >= '1' && input[1] <= '8')
        {
            return Position::fromChessNotation(input);
        }

        std::cout << "Invalid position. Enter again (e.g. e2): ";
    }
}
bool Game::readFromPosition(Position& from)
{
    std::string input;

    while (true)
    {
        std::cin >> input;

        if (input == "undo")
        {
            if (moveHistory.empty())
            {
                std::cout << "No moves to undo.\n";
                continue;
            }

            Move lastMove = moveHistory.popMove();

            board.undoMove(lastMove);

            switchTurn();

            std::cout << "\nMove undone successfully.\n\n";

            return false;
        }

        if (input.length() == 2 &&
            input[0] >= 'a' && input[0] <= 'h' &&
            input[1] >= '1' && input[1] <= '8')
        {
            from = Position::fromChessNotation(input);
            return true;
        }

        std::cout << "Invalid input. Enter square or 'undo': ";
    }
}

bool Game::isLegalMove(const std::vector<Position>& legalMoves,
                       const Position& destination) const
{
    for (const Position& move : legalMoves)
    {
        if (move == destination)
        {
            return true;
        }
    }

    return false;
}

void Game::switchTurn()
{
    currentTurn = (currentTurn == Color::WHITE)
                      ? Color::BLACK
                      : Color::WHITE;
}

void Game::start()
{
    while (gameState == GameState::RUNNING)
    {
        board.printBoard();

        std::cout << "\nCurrent Turn: "
                  << (currentTurn == Color::WHITE ? "White" : "Black")
                  << "\n\n";

        std::cout << "From (or type 'undo'): ";

        Position from;

        if (!readFromPosition(from))
        {
            continue;
        }

        Piece* piece = board.getPiece(from);

        if (piece == nullptr)
        {
            std::cout << "No piece at that position.\n\n";
            continue;
        }

        if (piece->getColor() != currentTurn)
        {
            std::cout << "You can only move your own pieces.\n\n";
            continue;
        }

        std::cout << "To: ";
        Position to = getPositionFromUser();

        std::vector<Position> legalMoves =
            moveValidator.getLegalMoves(board, piece, currentTurn);

        if (!isLegalMove(legalMoves, to))
        {
            std::cout << "Illegal move.\n\n";
            continue;
        }

        Piece* movedPiece = board.getPiece(from);
        Piece* capturedPiece = board.getPiece(to);

        Move move(from, to, movedPiece, capturedPiece);
        move.setMovedPieceHadMoved(movedPiece->getHasMoved());

        if (!moveValidator.isMoveLegal(board, move, currentTurn))
        {
            std::cout << "Move leaves your king in check.\n\n";
            continue;
        }
        if (movedPiece->getType() == PieceType::KING)
        {
            int diff = to.col - from.col;

            if (std::abs(diff) == 2)
            {
                int rookCol = (diff > 0) ? 7 : 0;

                Piece* rook =
                    board.getPiece(Position(from.row, rookCol));

                if (rook)
                    move.setRookHadMoved(rook->getHasMoved());
            }
        }
        board.makeMove(move);


        if (movedPiece->getType() == PieceType::PAWN)
        {
            bool promote =
                (movedPiece->getColor() == Color::WHITE && to.row == 0) ||
                (movedPiece->getColor() == Color::BLACK && to.row == 7);

            if (promote)
            {
                int choice;

                std::cout << "\nPawn Promotion!\n";
                std::cout << "1. Queen\n";
                std::cout << "2. Rook\n";
                std::cout << "3. Bishop\n";
                std::cout << "4. Knight\n";
                std::cout << "Choose: ";

                std::cin >> choice;

                PieceType newType = PieceType::QUEEN;

                switch (choice)
                {
                    case 2:
                        newType = PieceType::ROOK;
                        break;

                    case 3:
                        newType = PieceType::BISHOP;
                        break;

                    case 4:
                        newType = PieceType::KNIGHT;
                        break;

                    default:
                        newType = PieceType::QUEEN;
                        break;
                }
                board.promotePawn(to, newType);
            }
        }

        moveHistory.addMove(move);

        Color opponent =
            (currentTurn == Color::WHITE)
            ? Color::BLACK
            : Color::WHITE;

        bool inCheck =
            CheckDetector::isKingInCheck(board, opponent);

        if (inCheck)
        {
            if (!moveValidator.hasLegalMove(board, opponent))
            {
                board.printBoard();

                std::cout << "\n=========================\n";
                std::cout << "      CHECKMATE!\n";
                std::cout << "=========================\n\n";

                if (currentTurn == Color::WHITE)
                {
                    std::cout << "White Wins!\n";
                    gameState = GameState::WHITE_WON;
                }
                else
                {
                    std::cout << "Black Wins!\n";
                    gameState = GameState::BLACK_WON;
                }

                break;
            }

            std::cout << "\nCHECK!\n";
        }

        if (!inCheck &&
            !moveValidator.hasLegalMove(board, opponent))
        {
            board.printBoard();

            std::cout << "\n=========================\n";
            std::cout << "      STALEMATE!\n";
            std::cout << "=========================\n\n";

            std::cout << "Game Drawn!\n";

            gameState = GameState::DRAW;

            break;
        }
                switchTurn();

        std::cout << "\n";
    }
}