// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#include "ball.h"

Ball::Ball(double x_in, double y_in, double angle_in)
: coordinates(x_in, y_in){
  angle = angle_in;
}

Ball::Ball(Point center, double angle_in) : coordinates(center), angle(angle_in){}

Point Ball::getBallCoordinates() {
  return coordinates;
}

double Ball::getAngle(){
  return angle;
}

void Ball::setCoords(Point p){
  coordinates = p;
}

void Ball::setDeath(bool willDie_in){
  willDie = willDie_in;
}
bool Ball::getDeath(){
  return willDie;
}
