#include "ComparedSize.h"


ComparedSize::ComparedSize(void)
{
   Fig_id = -1;
   size_wrt_Fig_id = none_size_wrt_figure;
}


ComparedSize::~ComparedSize(void)
{
}

void ComparedSize::set_ComparedSize(int figure_id, QSize_wrt_Fig_Type size_tag){

  Fig_id = figure_id;
  size_wrt_Fig_id = size_tag;

}

ostream& operator<<(ostream &os, ComparedSize &cz)
{

  os << "[" << cz.Fig_id << ", ";

   switch (cz.size_wrt_Fig_id){

	case none_size_wrt_figure:  os << "none"; break;
	case much_smaller:  os << "much_smaller"; break;
	case half_size:  os << "half_size"; break;
	case a_bit_smaller:  os << "a_bit_smaller"; break;
	case similar_size:  os << "similar_size"; break;
	case a_bit_bigger:  os << "a_bit_bigger"; break;
	case double_size:  os << "double_size"; break;
	case much_bigger:  os << "much_bigger"; break;
	default:  os << "error"; break;

    }


  os << "] ";

  return os;
}

