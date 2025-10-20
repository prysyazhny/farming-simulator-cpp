#include <iostream>

#include "src/player.hpp"
#include "src/farm.hpp"
#include "src/farm_printer.hpp"
#include "src/carrot.hpp"
#include "src/ansi_clear.hpp"
#include <termios.h>
#include <unistd.h>

int main()
{
  struct TermiosGuard
  { // im not going to pretend like i know whats going on here but it lets you not need to press enter after each keypress
    termios orig;
    TermiosGuard()
    {
      tcgetattr(STDIN_FILENO, &orig);
      termios raw = orig;
      raw.c_lflag &= ~(ECHO | ICANON);
      raw.c_cc[VMIN] = 1;
      raw.c_cc[VTIME] = 0;
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    }
    ~TermiosGuard()
    {
      tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig);
    }
  } term_guard;

  Player player;
  Farm farm(10, 20, &player); // 10 x 20 grid
  FarmPrinter printer(&farm);
  bool game_in_progress = true;

  while (game_in_progress)
  {
    ansi_clear();
    std::cout << printer.pp() << std::endl;

    char c = 0;
    if (read(STDIN_FILENO, &c, 1) <= 0)
      continue;

    if (c == 'q')
    { // quit game
      game_in_progress = false;
    }
    else if (c == 'w')
    {
      player.move_up();
    }
    else if (c == 'a')
    {
      player.move_left();
    }
    else if (c == 's')
    {
      player.move_down();
    }
    else if (c == 'd')
    {
      player.move_right();
    }
    else if (c == 'c')
    { // plant carrot
      Carrot *carrot = new Carrot();
      farm.plant(player.row(), player.column(), carrot);
    }
    else if (c == 'e')
    { // end day
      farm.end_day();
    }
    else if (c == 'f')
    { // harvest
      Plot *plot = nullptr;
      farm.harvest(player.row(), player.column(), plot);
    }
  }
}
