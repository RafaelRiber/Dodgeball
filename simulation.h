#ifndef SIMULATION_H
#define SIMULATION_H

#include "player.h"
#include "ball.h"
#include "map.h"

class Simulation {
public:
  void read(char *file_name);       //Normal Read
  void read_error(char *file_name); //Error mode read

  void add_player(Player p);
  void add_ball(Ball b);

  void printPlayerSize();
  void printBallSize();

private:
  void decodeLine(std::string line);

  std::vector<Player> players;
  std::vector<Ball> balls;
};

#endif
