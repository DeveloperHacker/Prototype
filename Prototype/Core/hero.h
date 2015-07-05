#ifndef HERO_H
#define HERO_H

#include <iostream>
#include <QtCore>

#include "Core/point.h"
#include "Core/maze.h"

enum class Character {Minotavr, Human};
class Hero
{
protected:
    Point position;
    Point prev_position;
    Character character;
    unsigned step;
    unsigned review;
    char sign;

public:
    Hero() = default;
    Hero(Point position, Character character, unsigned step, unsigned review);
    virtual ~Hero() = default;

    unsigned get_step() const;
    Point get_position() const;
    Point get_prev_position() const;
    Character get_character() const;
    unsigned get_review() const;
    char get_sign() const;
    Hero& operator =(const Hero& temp);

    void step_to_north();
    void step_to_south();
    void step_to_west();
    void step_to_east();
    void step_back();
};

#endif
