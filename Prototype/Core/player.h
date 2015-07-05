#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>

#include "Core/hero.h"

class Player: public Hero
{
public:
    Player(Hero& temp);
    ~Player() = default;
};

#endif // PLAYER_H
