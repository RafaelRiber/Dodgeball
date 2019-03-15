#ifndef TOOLS_H
#define TOOLS_H

class Point {
public:
  Point(double x_in, double y_in);
  void getCoordinates (double &x_out, double &y_out) const;
private:
  double x, y;
};

class Segment {
public:
  Segment(double x_s_in, double y_s_in, double x_e_in, double y_e_in);
  double getLenght() const;

private:
  double x_start, y_start;
  double x_end, y_end;
};

class Circle {
public:

private:
  double center, radius;
};

class Square {
public:

private:

};

#endif
