#include "ComparedDistance.h"


ComparedDistance::ComparedDistance(void)
{
   Fig_A = -1;
   Fig_B = -1;
   distance_to_FigA = -1;
   distance_to_FigB = -1;
   compared_distance_AwrtB = none_distance;
}


ComparedDistance::~ComparedDistance(void)
{
}

void ComparedDistance::set_ComparedDistance(int fig_A, int fig_B, float dist_to_A, float dist_to_B, QComparedDistance_Type compared_distance_tag){

   Fig_A = fig_A;
   Fig_B = fig_B;
   distance_to_FigA = dist_to_A;
   distance_to_FigB = dist_to_B;
   compared_distance_AwrtB = compared_distance_tag;

}

ostream& operator<<(ostream &os, ComparedDistance &cd)
{

  os << "[" << cd.Fig_A << ", "<< cd.Fig_B << ", ";

  switch (cd.compared_distance_AwrtB){
    case none_distance: os << "none"; break;
    case closer_than: os << "closer_than"; break;
    case nearby: os << "nearby"; break;
    case further_than: os << "further_than"; break;
    default: os <<"error"; break;
    }

  os << "] ";

  return os;
}

