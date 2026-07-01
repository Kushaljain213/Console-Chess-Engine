#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "MoveHistory.h"
#include "MoveValidator.h"

enum class GameState{
    RUNNING,
    WHITE_WON,
    BLACK_WON,
    DRAW
};

class Game{
private:
    Board board;
    Player whitePlayer;
    Player blackPlayer;
    MoveHistory moveHistory;
    GameState gameState;
    Color currentTurn;
    MoveValidator moveValidator;

    Position getPositionFromUser() const;
    bool readFromPosition(Position& from);
    bool isLegalMove(const std::vector<Position>& legalMoves,const Position& destination) const;
    void switchTurn();

public:
    Game();
    void start();
};


#endif