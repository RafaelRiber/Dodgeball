// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "map.h"

Map::Map() : nbObstacles(0) {}

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
  nbObstacles += 1;
  return READING_SUCCESS;
}

void Map::removeObstacle(int row, int column){
  if(obstacleMap[row][column] == 0){
    std::cout<<"Error : Map::removeObstacle() : obstacle ("<<row<<", "<<column;
    std::cout<<") cannot be removed because it doesn't exist"<<std::endl;
    exit(0);
  }else{
    obstacleMap[row][column] = 0;
    nbObstacles -= 1;
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
  return nbObstacles;
  /*
  int nb(0);
  for (size_t i = 0; i < obstacleMap.size(); ++i)
  {
    for (size_t j = 0; j < obstacleMap[i].size(); ++j)
    {
      if (obstacleMap[i][j] == 1) nb++;
    }
  }
  return nb;
  */
}


int Map::cellToIndice(Cell cell){
  int indice(0);
  int cellX, cellY;
  cell.getCoordinates(cellX, cellY);

  for(int i(0); i<nbCell; i++){
    for(int j(0); j<nbCell; j++){
      if(obstacleMap[i][j] == 0){
        indice ++;
      }
      if(cellX == i && cellY == j){
        if(obstacleMap[i][j] > 0){
          std::cout<<"Map::cellToIndice : the cell is an obstacle"<<std::endl;
          exit(0);
        }else{
          return indice-1;
        }
      }
    }
  }
  std::cout<<"Map::cellToIndice : something went wrong !";
  std::cout<<" (maybe cell is out of bound)"<<std::endl;
  exit(0);
}

Cell Map::indiceToCell(int indice){
  int current(0);
  for(int i(0); i<nbCell; i++){
    for(int j(0); j<nbCell; j++){
      if(obstacleMap[i][j] == 0){
        current ++;
        if(current == indice+1){
          return Cell(i,j);
        }
      }
    }
  }
  std::cout<<"Map::indiceToCell : something went wrong !";
  std::cout<<" (maybe indice is out of bound)"<<std::endl;
  exit(0);
}

void Map::setIndiceToCell(){
  int nbSpot = nbCell*nbCell-nbObstacles;
  indiceToCell_table.resize(nbSpot, CELL_ERROR);
  for(int i(0); i < nbSpot; i++){
    indiceToCell_table[i] = indiceToCell(i);
  }
}

const std::vector<Cell>& Map::getIndiceToCell(){
  return indiceToCell_table;
}

void Map::setCellToIndice(){
  cellToIndice_table.resize(nbCell, std::vector<int>(nbCell));
  for(int i(0); i<nbCell; i++){
    for(int j(0); j<nbCell; j++){
      if(obstacleMap[i][j] == 0){
        cellToIndice_table[i][j] = cellToIndice(Cell (i,j));
      }else{
        cellToIndice_table[i][j] = -1;
      }
    }
  }
}

const std::vector<std::vector<int>>& Map::getCellToIndice(){
  return cellToIndice_table;
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
