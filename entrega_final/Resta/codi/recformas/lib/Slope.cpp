#include "Slope.h"


Slope::Slope(void)
{
   id_v1 = -1;
   id_v2 = -1;
   slope = 0.0;
}

Slope::~Slope(void)
{
}

void Slope::set_Slope(unsigned int id_vertex1, unsigned int id_vertex2, Point2D vertex1, Point2D vertex2, double slope_between_vertices){

   id_v1 = id_vertex1;
   id_v2 = id_vertex2;
   v1 = vertex1;
   v2 = vertex2;
   slope = slope_between_vertices;
}

ostream& operator<<(ostream &os, Slope &slope_object)
{

  os << "[ [" << slope_object.id_v1 << ", " << slope_object.id_v2 << "]," << slope_object.v1 << ", "<< slope_object.v2 << ", " << slope_object.slope;

  return os;
}
