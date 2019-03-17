#include <vector>
#include "ball.h"

static std::vector<Ball> balls;

Ball::Ball(double x_in, double y_in, double angle_in)
: coordinates(x_in, y_in){
  angle = angle_in;
}
