#include <cmath>
#include "tools.h"

Point::Point(double x_in, double y_in){
  x = x_in;
  y = y_in;
}

void Point::getCoordinates(double &x_out, double &y_out) const {
  x_out = this->x;
  y_out = this->y;
}


Segment::Segment(double x_s_in, double y_s_in, double x_e_in, double y_e_in){
  x_start = x_s_in;
  y_start = y_s_in;
  x_end = x_e_in;
  y_end = y_e_in;
}

double Segment::getLenght() const {
  double deltaX = (x_end - x_start);
  double deltaY = (y_end - y_start);
  return sqrt(pow((x_end - x_start), 2) + pow((y_end - y_start),2));
}
