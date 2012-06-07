#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

class RS
{

public:

  unsigned int id_fig_a;
  unsigned int id_fig_b;

  RS(void);
  RS(unsigned int a, unsigned int b);
  ~RS(void);
  
  void set_RS(unsigned int a, unsigned int b);


  friend ostream& operator<<(ostream &os, RS &rs);

};
