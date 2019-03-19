#ifndef SIMULATION_H
#define SIMULATION_H

#define MARGIN_DIVIDER  2

#include "player.h"
#include "ball.h"
#include "map.h"

class Simulation {
public:
  void read(char *file_name);       //Normal Read
  void read_error(char *file_name); //Error mode read

  void setSimParameters(int nbCell);
  double getRadius();

  void add_player(Player p);
  void playerBoundsCheck(Player p, double boundaryX, double boundaryY);
  void playerPlayerCheck(Player p, double readMargin);

  void add_ball(Ball b);
  void ballBoundsCheck(Ball b, double boundaryX, double boundaryY);
  void ballBallCheck(Ball b, double readMargin);

  void printPlayerSize();
  void printBallSize();

private:
  void decodeLine(std::string line);

  std::vector<Player> players;
  std::vector<Ball> balls;

  int nbCell;
  double radius;
};

#endif
