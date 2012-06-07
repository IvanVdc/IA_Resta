#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "Point2D.h"

using namespace std;

class Slope
{

public:

  unsigned int id_v1;
  unsigned int id_v2;

  Point2D v1;
  Point2D v2;

  double slope;

  Slope(void);
  ~Slope(void);
  
  void set_Slope(unsigned int id_v1, unsigned int id_v2, Point2D v1, Point2D v2, double slope);

  friend ostream& operator<<(ostream &os, Slope &slope_object);

};
