// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include "player.h"
#include "ball.h"
#include "map.h"
#include "define.h"

class Simulation {
public:
  void read(char *file_name);       //Normal Read
  void read();
  void read_error(char *file_name); //Error mode read
  Map getMap();
  std::vector<Player> getPlayers();
  std::vector<Ball> getBalls();
  int getNbCell();
  double getPlayerRadius();

private:
  void setSimParameters(int nbCell);
  double getBallRadius();

  bool add_player(Player p);
  bool playerBoundsCheck(Player p, double boundaryX, double boundaryY);
  bool playerPlayerCheck(Player p);

  bool add_ball(Ball b,int indice, const std::vector<std::vector<int>> &map);
  bool ballBoundsCheck(Ball b, double boundaryX, double boundaryY);
  bool ballBallCheck(Ball b);

  bool add_obstacle(unsigned int row, unsigned int column, unsigned int indice,Map &m);
  bool obstaclePlayerCheck(Rectangle obstacle, unsigned int radius);

  bool playerBallCheck(Ball b);
  bool ballObstacleCheck(Point ball, int indice,
                         const std::vector<std::vector<int> > &map);

  bool pointObstacleCollision(Point point, int obstRow, int obstColumn,
                                double totalMargin);

  void printPlayerSize();
  void printBallSize();

  bool openFile(std::string fileName);
  bool decodeLine(std::string line);


  std::vector<Player> players;
  std::vector<Ball> balls;

  int nbCell;
  double readMargin;
  double playerRadius;
  double ballRadius;

  Map m;
};

#endif
