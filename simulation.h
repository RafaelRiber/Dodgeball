// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "player.h"
#include "ball.h"
#include "map.h"
#include "define.h"
#include "error.h"

class Simulation {
public:
  void read(char *file_name);
  void read_error(char *file_name);
  void read_step(char *input_file, char *output_file);
  void saveToFile(char *file_name);
  void reset();
  void start();
  void stop();
  bool isRunning();
  bool isReadSuccessful();
  Map getMap();
  std::vector<Player> getPlayers();
  std::vector<Ball> getBalls();
  int getNbCell();
  int getNbBalls();
  double getPlayerRadius();
  double getBallRadius();

  void simulate_one_step();

private:
  void setSimParameters(int nbCell);

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
  bool pointObstacleCollision(Point point, Cell obst, double totalMargin);
  void printPlayerSize();
  void printBallSize();
  bool openFile(std::string fileName);
  bool decodeLine(std::string line);

  void find_targets();
  void move_players();
  void set_players_direction();
  bool has_direct_line_of_sight(Point start,  Point end);
  bool has_direct_line_of_sight(Player &player, Player &target);
  Vector floyd_next_move(Player player);
  void refresh_floyd();
  void fire_balls();
  void move_balls();
  void incrementCount();
  void ball_ball_collisions();
  void ball_player_collisions();
  void ball_obstacle_collisions();
  void ballOutOfBoundsDeaths();
  void playerOutOfBoundsDeaths();
  void purge_game();
  void purgeBalls();
  void purgePlayers();
  void reset_targets();

  void dump();
  void dumpPlayer();
  void dumpFloyd();

  std::vector<Player> players;
  std::vector<Ball> balls;
  int nbCell;
  double readMargin;
  double gameMargin;
  double playerRadius;
  double playerSpeed;
  double ballRadius;
  double ballSpeed;
  bool running = false;
  bool successfulRead = false;
  Map m;

  std::vector<std::vector<double>>floyd_distances;
};

#endif
