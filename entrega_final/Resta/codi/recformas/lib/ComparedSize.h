#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

//enum QSize_wrt_Fig_Type {none_size_wrt_figure, smaller_than_half, half, larger_than_half, equal_size, smaller_than_double, double_size, larger_than_double};

//enum QSize_wrt_Fig_Type {none_size_wrt_figure, smaller_than, similar_size, larger_than};

enum QSize_wrt_Fig_Type {none_size_wrt_figure, much_smaller, half_size, a_bit_smaller, similar_size, a_bit_bigger, double_size, much_bigger};

class ComparedSize
{

public:

  int Fig_id;
  QSize_wrt_Fig_Type  size_wrt_Fig_id;

  ComparedSize(void);
  ~ComparedSize(void);
  void set_ComparedSize(int figure_id, QSize_wrt_Fig_Type size_tag);
  friend ostream& operator<<(ostream &os, ComparedSize &cz);

};
