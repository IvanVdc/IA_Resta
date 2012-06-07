#include "RelativeOrientation.h"


RelativeOrientation::RelativeOrientation(void)
{
}


RelativeOrientation::~RelativeOrientation(void)
{
  VRel_orient.clear();
}


int RelativeOrientation::orientation_in_vector(QRelative_Orientation_Type relOrient){

	int is_in_vector = 0;	

	for (unsigned int i = 0; i < VRel_orient.size(); i++){
		if (VRel_orient[i] == relOrient)
			is_in_vector = 1;	
	}


	return is_in_vector;
}

void RelativeOrientation::add_RelOrientation(QRelative_Orientation_Type orientation_tag){
//No añade etiquetas repetidas

  
  if (VRel_orient.size() == 0)
	VRel_orient.push_back(orientation_tag);
  else{

	if (!orientation_in_vector(orientation_tag))
		VRel_orient.push_back(orientation_tag);

  }

}


ostream& operator<<(ostream &os, RelativeOrientation &oo)
{

  os << "[" << oo.rs << ", [";

  for (unsigned int i = 0; i < oo.VRel_orient.size(); i++){
  	switch (oo.VRel_orient[i]){
    		case none_rel_orientation: os << "none"; break;
    		case lf: os << "left_front"; break;
    		case sf: os << "straight_front"; break;
    		case rf: os << "right_front"; break;
    		case l: os << "left"; break;
    		case idf: os << "identical_front"; break;
    		case r: os << "right"; break;
    		case lm: os << "left_middle"; break;
    		case sm: os << "same_middle"; break;
    		case rm: os << "right_middle"; break;
    		case ibl: os << "identical_back_left"; break;
    		case ib: os << "identical_back"; break;
    		case ibr: os << "identical_back_right"; break;
    		case bl: os << "back_left"; break;
		case sb: os << "straight_back"; break;
    		case br: os << "back_right"; break;
    		default: os <<"error"; break;
    	}

	if (i != oo.VRel_orient.size()-1) os <<", ";
  }

  os << "] ] ";

  return os;
}
