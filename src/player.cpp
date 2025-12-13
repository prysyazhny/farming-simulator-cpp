#include "player.hpp"

int Player::row() const
{
  return current_row;
}

int Player::column() const
{
  return current_column;
}

void Player::move_up()
{
  if (current_row > 0)
    current_row--;
}

void Player::move_down()
{
  if (current_row < bounds_rows - 1)
    current_row++;
}

void Player::move_left()
{
  if (current_column > 0)
    current_column--;
}

void Player::move_right()
{
  if (current_column < bounds_columns - 1)
    current_column++;
}
