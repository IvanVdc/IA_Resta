#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

enum QComparedDistance_Type {none_distance, closer_than, nearby, further_than};



class ComparedDistance
{

public:

  int Fig_A;
  int Fig_B;

  float distance_to_FigA;
  float distance_to_FigB;
  QComparedDistance_Type  compared_distance_AwrtB;

  ComparedDistance(void);
  ~ComparedDistance(void);
  void set_ComparedDistance(int fig_A, int fig_B, float dist_to_A, float dist_to_B, QComparedDistance_Type compared_distance_tag);

  friend ostream& operator<<(ostream &os, ComparedDistance &cd);

};
