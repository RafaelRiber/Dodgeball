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
  Point getPlayerCoordinates();
  int getNbt();

private:
  Point coordinates;
  int nbt, count;
};

#endif
