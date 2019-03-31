// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

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
  double getPlayerRadius();
  double getBallRadius();

  void add_player(Player p);
  void playerBoundsCheck(Player p, double boundaryX, double boundaryY);
  void playerPlayerCheck(Player p);

  void add_ball(Ball b,int indice, const std::vector<std::vector<int>> &map);
  void ballBoundsCheck(Ball b, double boundaryX, double boundaryY);
  void ballBallCheck(Ball b);

  void add_obstacle(unsigned int row, unsigned int column, unsigned int indice,Map &m);
  void obstaclePlayerCheck(Rectangle obstacle, unsigned int radius);

  void playerBallCheck(Ball b);
  void ballObstacleCheck(Point ball, int indice,
                         const std::vector<std::vector<int> > &map);

  bool pointOsbstacleCollistion(Point point, int obstRow, int obstColumn,
                                double totalMargin);

  void printPlayerSize();
  void printBallSize();

private:
  void decodeLine(std::string line);

  std::vector<Player> players;
  std::vector<Ball> balls;

  int nbCell;
  double readMargin;
  double playerRadius;
  double ballRadius;
};

#endif
