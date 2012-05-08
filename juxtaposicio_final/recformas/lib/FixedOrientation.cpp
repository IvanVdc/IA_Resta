#include "FixedOrientation.h"


FixedOrientation::FixedOrientation(void)
{
   Fig_id = -1;
}


FixedOrientation::~FixedOrientation(void)
{
  VFixed_orient.clear();
}

void FixedOrientation::set_Figure_id(int figure_id){

   Fig_id = figure_id;
}


int FixedOrientation::orientation_in_vector(QFixed_Orientation_Type fOrient){

	int is_in_vector = 0;	

	for (unsigned int i = 0; i < VFixed_orient.size(); i++){
		if (VFixed_orient[i] == fOrient)
			is_in_vector = 1;	
	}


	return is_in_vector;
}

void FixedOrientation::add_FixedOrientation(QFixed_Orientation_Type orientation_tag){
//No añade etiquetas repetidas

  //VFixed_orient.push_back(orientation_tag);
 
  if (VFixed_orient.size() == 0)
	VFixed_orient.push_back(orientation_tag);
  else{

	if (!orientation_in_vector(orientation_tag))
		VFixed_orient.push_back(orientation_tag);

  }

}

ostream& operator<<(ostream &os, FixedOrientation &oo)
{

  os << "[" << oo.Fig_id << ", [";

  for (unsigned int i = 0; i < oo.VFixed_orient.size(); i++){
  	switch (oo.VFixed_orient[i]){
    		case none_orientation: os << "none"; break;
    		case _front: os << "front"; break;
    		case _back: os << "back"; break;
    		case _left: os << "left"; break;
    		case _right: os << "right"; break;
    		case _front_left: os << "front_left"; break;
    		case _front_right: os << "front_right"; break;
    		case _back_left: os << "back_left"; break;
    		case _back_right: os << "back_right"; break;
		case _centre: os << "centre"; break;
    		default: os <<"error"; break;
    	}

	if (i != oo.VFixed_orient.size()-1) os <<", ";
  }

  os << "] ] ";

  return os;
}

