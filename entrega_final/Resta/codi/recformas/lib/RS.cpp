#include "RS.h"


RS::RS(void)
{
}

RS::RS(unsigned int point_a, unsigned int point_b)
{
   id_fig_a = point_a;
   id_fig_b = point_b;
}

RS::~RS(void)
{
}

void RS::set_RS(unsigned int point_a, unsigned int point_b){

   id_fig_a = point_a;
   id_fig_b = point_b;
}

ostream& operator<<(ostream &os, RS &oo)
{

  os << "[" << oo.id_fig_a << ", " << oo.id_fig_b << "]";

  return os;
}
