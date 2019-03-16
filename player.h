#ifndef PLAYER_H
#define PLAYER_H

#include "tools.h"

class Player {
public:
  Player(double x_in, double y_in, int nbt_in, int count_in);

private:
  Point coordinates;
  int nbt, count;
};



#endif
