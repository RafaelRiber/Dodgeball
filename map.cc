#include "map.h"
#include "tools.h"
#include "define.h"
#include <iostream>

Map::Map(int nbCellIn){

  nbCell = nbCellIn;

  //TODO: SIZE CHECKING

  obstacleMap.resize(nbCell);
  for (int i = 0; i < nbCell; ++i) obstacleMap[i].resize(nbCell);

  for (auto &v: obstacleMap) {
    std::fill(v.begin(), v.end(), 0);
  }
};

void Map::setObstacle(int line, int column){
  obstacleMap[line][column] = 1;
}

void Map::setEmpty(int line, int column){
  obstacleMap[line][column] = 0;
}

// Dumps map in terminal
void Map::dump(){
  for (int i = 0; i < obstacleMap.size(); i++)
  {
    for (int j = 0; j < obstacleMap[i].size(); j++)
    {
        std::cout << obstacleMap[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
