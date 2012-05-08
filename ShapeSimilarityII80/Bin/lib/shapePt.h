#pragma once

#include <iostream>
#include <vector>
#include <cstdio>
#include <math.h>
#include "Point2D.h"

using namespace std;

class  shapePt {
public:

  Point2D pt; //maxC tendra valor si shape es una curva
  int shape; //straight: 0, curve: 1

  shapePt(void);
  shapePt(Point2D p, int s=-1);
  
  shapePt operator=(shapePt p);
  bool operator==(shapePt &p);
  bool operator!=(shapePt &p);  
  friend ostream& operator<<(ostream& os, shapePt &p);
};
