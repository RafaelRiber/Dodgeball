// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include <vector>
#include "ball.h"

Ball::Ball(double x_in, double y_in, double angle_in)
: coordinates(x_in, y_in){
  angle = angle_in;
}

Point Ball::getBallCoordinates() {
  return coordinates;
}

double Ball::getAngle(){
  return angle;
}
