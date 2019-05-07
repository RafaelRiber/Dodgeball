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
  Map();

  std::vector<std::vector<int>> getMap();
  void setSize(int nbCellIn);
  bool setObstacle(int row, int column);
  void removeObstacle(int row, int column);
  void reset();
  void dump();
  int getNbObst();

  void setIndiceToCell();
  const std::vector<Cell>& getIndiceToCell();
  void setCellToIndice();
  const std::vector<std::vector<int>>& getCellToIndice();

private:
  bool obstacleIndexCheck(int row, int column);
  bool obstacleDuplicateCheck(int row, int column);

  int cellToIndice(Cell cell);
  Cell indiceToCell(int indice);
  std::vector<std::vector<int>> cellToIndice_table;
  std::vector<Cell> indiceToCell_table;

  int nbCell;
  int nbObstacles;
  std::vector<std::vector<int> > obstacleMap;
};

#endif
