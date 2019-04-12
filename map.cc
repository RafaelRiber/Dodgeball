// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "map.h"

void Map::setSize(int nbCellIn){
  nbCell = nbCellIn;
  obstacleMap.resize(nbCell);
  for (int i = 0; i < nbCell; ++i) obstacleMap[i].resize(nbCell);
  for (auto &v: obstacleMap) {
    std::fill(v.begin(), v.end(), 0);
  }
}

std::vector<std::vector<int>> Map::getMap(){
    return obstacleMap;
}

bool Map::setObstacle(int row, int column){
  if(!obstacleIndexCheck(row, column))     return READING_FAIL;
  if(!obstacleDuplicateCheck(row, column)) return READING_FAIL;
  obstacleMap[row][column] = 1;
  return READING_SUCCESS;
}

void Map::setEmpty(int row, int column){
  obstacleMap[row][column] = 0;
}

void Map::dump(){
  for (size_t i = 0; i < obstacleMap.size(); i++)
  {
    for (size_t j = 0; j < obstacleMap[i].size(); j++)
    {
        std::cout << obstacleMap[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool Map::obstacleIndexCheck(int row, int column){
  if (row >= (int) obstacleMap.size()){
    std::cout << OBSTACLE_VALUE_INCORRECT(row) << std::endl;
    return READING_FAIL;
  }
  if (column >= (int)obstacleMap[1].size()){
    std::cout << OBSTACLE_VALUE_INCORRECT(column) << std::endl;
    return READING_FAIL;
  }
  return READING_SUCCESS;
}

bool Map::obstacleDuplicateCheck(int row, int column){
  if (obstacleMap[row][column]){
    std::cout << MULTI_OBSTACLE(row, column) << std::endl;
    return READING_FAIL;
  }
  return READING_SUCCESS;
}

void Map::reset(){
  obstacleMap = std::vector<std::vector<int>> ();
}

int Map::getNbObst(){
  int nb(0);
  for (size_t i = 0; i < obstacleMap.size(); ++i)
  {
    for (size_t j = 0; j < obstacleMap[i].size(); ++j)
    {
      if (obstacleMap[i][j] == 1) nb++;
    }
  }
  return nb;
}
