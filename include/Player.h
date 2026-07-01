#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Piece.h"


class Player{
private:
    std::string name;
    Color color;
public:
    Player();
    Player(const std::string& name, Color color);
    std::string getName() const;
    Color getColor() const;
};

#endif