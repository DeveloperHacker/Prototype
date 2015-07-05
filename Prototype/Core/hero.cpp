#include "Core/hero.h"

Hero::Hero(Point position, Character character, unsigned step, unsigned review)
{
    this->position = position;
    this->prev_position = position;
    this->character = character;
    this->step = step;
    this->review = review;
    if (this->character == Character::Human) sign = 'H';
    if (this->character == Character::Minotavr) sign = 'M';
}

char Hero::get_sign() const
{
    return sign;
}

unsigned Hero::get_review() const
{
    return review;
}

unsigned Hero::get_step() const
{
    return step;
}

Point Hero::get_position() const
{
    return position;
}

Point Hero::get_prev_position() const
{
    return prev_position;
}

Character Hero::get_character() const
{
    return character;
}

void Hero::step_to_north()
{
    prev_position = position;
    position.y -= 1;
}

void Hero::step_to_south()
{
    prev_position = position;
    position.y += 1;
}

void Hero::step_to_west()
{
    prev_position = position;
    position.x -= 1;
}

void Hero::step_to_east()
{
    prev_position = position;
    position.x += 1;
}

void Hero::step_back()
{
    position = prev_position;
}

Hero& Hero::operator =(const Hero& temp)
{
    character = temp.get_character();
    position = temp.get_position();
    prev_position = temp.get_prev_position();
    step = temp.get_step();
    sign = temp.get_sign();
    return *this;
}
