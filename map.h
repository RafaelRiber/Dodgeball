// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef MAP_H
#define MAP_H

#define READING_FAIL     false;
#define READING_SUCCESS  true;

#include <vector>

class Map {
public:
  std::vector<std::vector<int>> getMap();
  void setSize(int nbCellIn);
  bool setObstacle(int row, int column);
  void setEmpty(int row, int column);
  void dump();

private:
  bool obstacleIndexCheck(int row, int column);
  bool obstacleDuplicateCheck(int row, int column);

  int nbCell;
  std::vector<std::vector<int> > obstacleMap;
};

#endif
