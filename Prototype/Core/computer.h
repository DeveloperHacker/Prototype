#ifndef COMPUTER_H
#define COMPUTER_H

#include <iostream>

#include "Core/hero.h"

struct SegmentDistribution
{
    unsigned probability;
    Point shift;
    bool use;
};

class Computer: public Hero
{
public:
    Computer(Hero& temp);
    ~Computer() = default;

    bool movement(Maze level_map);
    bool move_to_hero(Maze &level_map);
};

#endif // COMPUTER_H
