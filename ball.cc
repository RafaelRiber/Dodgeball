#include <vector>
#include <iostream>
#include "ball.h"

static std::vector<Ball> balls;

Ball::Ball(double x_in, double y_in, double angle_in)
: coordinates(x_in, y_in){
  angle = angle_in;
}

void Ball::add(){
  balls.push_back(*this);
}

void ballPrintSize(){
  std::cout << "Balls vector size: " << balls.size() << std::endl;
}
