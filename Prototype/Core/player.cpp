#include "Core/player.h"


Player::Player(Hero& temp)
{
    position = temp.get_position();
    prev_position = position;
    character = temp.get_character();
    step = temp.get_step();
    sign = temp.get_sign();
    review = temp.get_review();
}

