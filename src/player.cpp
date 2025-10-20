#include "player.hpp"

int Player::row()
{
    return current_row;
}

int Player::column()
{
    return current_column;
}

void Player::move_up()
{
    if (current_row > 0)
    {
        current_row -= 1;
    }
}

void Player::move_down()
{
    if (current_row < 9)
    {
        current_row += 1;
    }
}

void Player::move_left()
{
    if (current_column > 0)
    {
        current_column -= 1;
    }
}

void Player::move_right()
{
    if (current_column < 39)
    {
        current_column += 1;
    }
}