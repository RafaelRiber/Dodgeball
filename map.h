#ifndef MAP_H
#define MAP_H

#include <vector>

// Size of map is nbCell x nbCell
// and must be minimum MIN_CELL (3x3) and maximum [-DIM_MAX, DIM_MAX] (800x800)

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
  int nbCell;  //Must be at least MIN_CELL
  std::vector<std::vector<int> > obstacleMap;
};

#endif
