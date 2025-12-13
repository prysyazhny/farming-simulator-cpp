#include <iostream>

#include "src/player.hpp"
#include "src/farm.hpp"
#include "src/farm_printer.hpp"
#include "src/ansi_clear.hpp"
#include <termios.h>
#include <unistd.h>

#include "src/vegetables/carrot.hpp"
#include "src/vegetables/beet.hpp"
#include "src/vegetables/lettuce.hpp"
#include "src/vegetables/spinach.hpp"
#include "src/vegetables/brussels_sprouts.hpp"

int main()
{
  struct TermiosGuard
  {
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

  int grid_rows = 10;
  int grid_columns = 40;

  Player player(grid_rows, grid_columns);
  Farm farm(grid_rows, grid_columns, &player);
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
    {
      game_in_progress = false;
    }
    else if (c == 'w')
    {
      player.move_up();
      farm.check_bunny_scared();
    }
    else if (c == 'a')
    {
      player.move_left();
      farm.check_bunny_scared();
    }
    else if (c == 's')
    {
      player.move_down();
      farm.check_bunny_scared();
    }
    else if (c == 'd')
    {
      player.move_right();
      farm.check_bunny_scared();
    }
    else if (c == 'e')
    {
      farm.end_day();
    }
    else if (c == 'f')
    {
      Plot *plot = nullptr;
      farm.harvest(player.row(), player.column(), plot);
    }
    else if (c == ' ')
    {
      Plot *plot = nullptr;
      farm.water(player.row(), player.column(), plot);
    }
    else if (c == 'c')
    {
      Carrot *carrot = new Carrot();
      farm.plant(player.row(), player.column(), carrot);
    }
    else if (c == 'l')
    {
      Lettuce *lettuce = new Lettuce();
      farm.plant(player.row(), player.column(), lettuce);
    }
    else if (c == 'p')
    {
      Spinach *spinach = new Spinach();
      farm.plant(player.row(), player.column(), spinach);
    }
    else if (c == 'b')
    {
      Beet *beet = new Beet();
      farm.plant(player.row(), player.column(), beet);
    }
    else if (c == 'r')
    {
      BrusselsSprouts *brussels_sprouts = new BrusselsSprouts();
      farm.plant(player.row(), player.column(), brussels_sprouts);
    }
  }
}
