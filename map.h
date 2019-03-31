// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef MAP_H
#define MAP_H

#include <vector>

class Map {
public:
  std::vector<std::vector<int>> getMap();
  void setSize(int nbCellIn);
  void setObstacle(int row, int column);
  void setEmpty(int row, int column);
  void dump();

  void obstacleIndexCheck(int row, int column);
  void obstacleDuplicateCheck(int row, int column);

private:
  int nbCell;
  std::vector<std::vector<int> > obstacleMap;
};

#endif
