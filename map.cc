#include "map.h"
#include "tools.h"


Map::Map(int nbCell){
  obstacleMap.resize(nbCell);
  for (int i = 0; i < nbCell; ++i) obstacleMap[i].resize(nbCell);

  for (auto &v: obstacleMap) {
    std::fill(v.begin(), v.end(), 0);
  }
};
