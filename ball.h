#ifndef BALL_H
#define BALL_H

#include "tools.h"

class Ball{
public:
  Ball(double x_in, double y_in, double angle_in);
  Point getBallCoordinates();

private:
  Point coordinates;
  double angle;
};

#endif
