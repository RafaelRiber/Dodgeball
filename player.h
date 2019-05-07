// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef PLAYER_H
#define PLAYER_H

#include "tools.h"

class Player {
public:
  Player(double x_in, double y_in, int nbt_in, int count_in);

  //--GETTERS--
  Point getPlayerCoordinates();
  int getNbt();
  int getCount();
  Vector getNextMove();
  Player* getTarget();
  Point getTargetCoordinates();
  bool getHasLineOfSight();

  //--SETTERS--
  void setNextMove(Vector v);
  void setTarget(Player &target);
  void setHasLineOfSight(bool b);

  //--FUNCTIONS--
  void make_next_move();
  void incrementPlayerCount();
  void got_hit();
  void dump();

private:
  Point coordinates;
  int nbt, count;
  Player* target;
  bool has_line_of_sight;
  Vector next_move;
};

#endif
