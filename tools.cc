#include "tools.h"

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

void Point::getCoordinates(double &xOut, double &yOut) const {
  xOut = this->x;
  yOut = this->y;
}
