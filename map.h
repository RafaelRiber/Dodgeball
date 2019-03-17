#ifndef MAP_H
#define MAP_H

#include <vector>

// Size of map is nbCell x nbCell
// and must be minimum MIN_CELL (3x3) and maximum [-DIM_MAX, DIM_MAX] (800x800)

class Map {
public:
  Map(int nbCell);
  void setObstacle(int line, int column);
  void setEmpty(int line, int column);
  void dump();

private:
  int nbCell;  //Must be at least MIN_CELL
  std::vector<std::vector<int> > obstacleMap;
};

#endif
