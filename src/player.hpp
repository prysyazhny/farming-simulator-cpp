#pragma once

class Player
{
private:
  int current_row = 0;
  int current_column = 0;

  int bounds_rows;
  int bounds_columns;

public:
  Player(int boundRows, int boundColumns) : bounds_rows(boundRows), bounds_columns(boundColumns) {}
  int row();
  int column();
  void move_up();
  void move_down();
  void move_left();
  void move_right();
};
