// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <vector>
#include "tools.h"
#include "define.h"
#include "error.h"

class Map {
public:
  std::vector<std::vector<int>> getMap();
  void setSize(int nbCellIn);
  bool setObstacle(int row, int column);
  void setEmpty(int row, int column);
  void reset();
  void dump();
  int getNbObst();

private:
  bool obstacleIndexCheck(int row, int column);
  bool obstacleDuplicateCheck(int row, int column);

  int nbCell;
  std::vector<std::vector<int> > obstacleMap;
};

#endif
