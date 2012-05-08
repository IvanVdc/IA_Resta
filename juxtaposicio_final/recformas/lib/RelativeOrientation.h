#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include "RS.h"

using namespace std;

enum QRelative_Orientation_Type {none_rel_orientation, lf, sf, rf, l, idf, r, lm, sm, rm, ibl, ib, ibr, bl, sb, br};


class RelativeOrientation
{

public:

  RS rs;

  vector<QRelative_Orientation_Type>  VRel_orient;


  RelativeOrientation(void);
  ~RelativeOrientation(void);

  int orientation_in_vector(QRelative_Orientation_Type relOrient);
  void add_RelOrientation(QRelative_Orientation_Type rel_orient_tag);
  
  friend ostream& operator<<(ostream &os, RelativeOrientation &rel_orient_object);

};
