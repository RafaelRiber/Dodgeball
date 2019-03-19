#include <iostream>
#include "map.h"
#include "tools.h"
#include "define.h"
#include "error.h"

void Map::setSize(int nbCellIn){

  nbCell = nbCellIn;

  obstacleMap.resize(nbCell);
  for (int i = 0; i < nbCell; ++i) obstacleMap[i].resize(nbCell);

  for (auto &v: obstacleMap) {
    std::fill(v.begin(), v.end(), 0);
  }
};

void Map::setObstacle(int row, int column){

  //Obstacle index check
  obstacleIndexCheck(row, column);

  //Obstacle duplicate check
  obstacleDuplicateCheck(row, column);
  
  obstacleMap[row][column] = 1;
}

void Map::setEmpty(int row, int column){
  obstacleMap[row][column] = 0;
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

void Map::obstacleIndexCheck(int row, int column){
  //Obstacle Index
  if (row >= obstacleMap.size()){
    std::cout << OBSTACLE_VALUE_INCORRECT(row) << std::endl;
    exit(0);
  }
  if (column >= obstacleMap[1].size()){
    std::cout << OBSTACLE_VALUE_INCORRECT(column) << std::endl;
    exit(0);
  }
}

void Map::obstacleDuplicateCheck(int row, int column){
  if (obstacleMap[row][column]){
    std::cout << MULTI_OBSTACLE(row, column) << std::endl;
    exit(0);
  }
}
