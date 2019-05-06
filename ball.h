// EPFL - Programmation Orientée Projet (en C++) - COM-112(a)
// Projet Dodgeball
// Auteurs: Rafael RIBER  - SCIPER: 296142
//          Valentin RIAT - SCIPER: 289121

#ifndef BALL_H
#define BALL_H

#include "tools.h"

class Ball{
public:
  Ball(double x_in, double y_in, double angle_in);
  Point getBallCoordinates();
  double getAngle();
  void setCoords(Point p);

private:
  Point coordinates;
  double angle;
};

#endif
