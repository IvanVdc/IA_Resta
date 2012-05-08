#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

enum QFixed_Orientation_Type {none_orientation, _front, _back, _left, _right, _front_left, _front_right, _back_left, _back_right, _centre};


class FixedOrientation
{

public:

  int Fig_id;
  vector<QFixed_Orientation_Type>  VFixed_orient;

  FixedOrientation(void);
  ~FixedOrientation(void);

  void set_Figure_id(int figure_id);
  void add_FixedOrientation(QFixed_Orientation_Type orientation_tag);
  int orientation_in_vector(QFixed_Orientation_Type fOrient);
  
  friend ostream& operator<<(ostream &os, FixedOrientation &orientation_object);

};
