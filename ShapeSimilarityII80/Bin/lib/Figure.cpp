#include "Figure.h"

#define INF_SLOPE	1000

using namespace std;

Figure::Figure(void)
{
  area = 0;
  comp = false;
  curves = -1;
  ncomponents = 0;
  nvertices = 0;
  nqpts = 0;
  isIntern = false;
  regular = false;
  color = "";
	description = "";
	name = "";
  convexity = -1;
}

Figure::~Figure(void)
{
  vertices.clear();
  infoVertices.clear();
  components.clear();
  containers.clear();
  qualPtV.clear();
  border.clear();
  neighbours.clear();
}

Figure::Figure(vector<Point2D> v, int ident)
{
  vertices = v;
  id = ident;
  area = 0;
  comp = false;
  curves = -1;
  ncomponents = 0;
	nvertices = 0;
	nqpts = 0;
  convexity = -1;
	color = "";
	description = "";
	name = "";
}

void Figure::setArea(void)
{
  area = 0;
  int i,j;
  double xi,yi,xj,yj;

  i=0;
  int N = (infoVertices.size())-1;

  //Metodo de Productos Cruzados
  while(i<N){
    j = (i + 1);
    xi = infoVertices[i].pt.x;
    xj = infoVertices[j].pt.x;
    yi = infoVertices[i].pt.y;
    yj = infoVertices[j].pt.y;
    area += xi * yj - yi * xj;
    i++;
  }
  xi = infoVertices[N].pt.x;
  xj = infoVertices[0].pt.x;
  yi = infoVertices[N].pt.y;
  yj = infoVertices[0].pt.y;
  area += ((xi * yj) - (yi * xj));
  area = fabs(area) / 2.0;
}

void Figure::setCentroid(void)
{
  //le hemos pasado un vector de puntos2D donde estan almacenados todos los vértices del poligono
  int N = (infoVertices.size())-1;
  double cx=0,cy=0;

  if (area == 0)
    setArea();

  double areaTemp = area;

  int i,j;
  double p1xi,p1yi,p1xj,p1yj;
	double factor=0;
  i=0;
  while(i<N)
  {
	  j = (i + 1);
    p1xi = infoVertices[i].pt.x;
		p1xj = infoVertices[j].pt.x;
    p1yi = infoVertices[i].pt.y;
    p1yj = infoVertices[j].pt.y;
    factor = (p1xi*p1yj - p1xj*p1yi);
    cx += (p1xi + p1xj) * factor;
    cy += (p1yi + p1yj) * factor;
    i++;
  }
  p1xi = infoVertices[N].pt.x;
  p1xj = infoVertices[0].pt.x;
  p1yi = infoVertices[N].pt.y;
  p1yj = infoVertices[0].pt.y;
  factor =(p1xi*p1yj - p1xj*p1yi);
  cx += (p1xi + p1xj) * factor;
  cy += (p1yi + p1yj) * factor;

  areaTemp *= 6.0;
  double factor2 = 1.0/areaTemp;
  cx *= factor2;
  cy *= factor2;
  cx = round(cx);
  cy = round(cy);
  centroid = Point2D (cx, cy);
}

void Figure::setAreaCentroid(void)
{
  area = 0;
  int i,j;
  double xi,yi,xj,yj;

  double cx=0,cy=0;

  double p1xi,p1yi,p1xj,p1yj;
  double factor=0, areaTemp;


  i=0;
  int N = (border.size())-1;

  //Metodo de Productos Cruzados
  while(i<N)
	{
		//Para el area
    j = (i + 1);
    xi = border[i].x;
    xj = border[j].x;
    yi = border[i].y;
    yj = border[j].y;
    area += xi * yj - yi * xj;

		//Para el centroide
		p1xi = border[i].x;
		p1xj = border[j].x;
    p1yi = border[i].y;
    p1yj = border[j].y;
    factor = (p1xi*p1yj - p1xj*p1yi);
    cx += (p1xi + p1xj) * factor;
    cy += (p1yi + p1yj) * factor;

    i++;
  }
  xi = border[N].x;
  xj = border[0].x;
  yi = border[N].y;
  yj = border[0].y;
  area += ((xi * yj) - (yi * xj));
  area = fabs(area) / 2.0;

  p1xi = border[N].x;
  p1xj = border[0].x;
  p1yi = border[N].y;
  p1yj = border[0].y;
  factor =(p1xi*p1yj - p1xj*p1yi);
  cx += (p1xi + p1xj) * factor;
  cy += (p1yi + p1yj) * factor;

  areaTemp = area * 6.0;
	double factor2 = 1.0/areaTemp;
	cx *= factor2;
	cy *= factor2;
  cx = round(cx);
  cy = round(cy);
  centroid = Point2D (cx, cy);
}

void Figure::setCentroidAlt(void)
{
  double cx=0,cy=0;
  int sz = infoVertices.size();

  for (int i=0; i<sz; i++)
  {
    cx += infoVertices[i].pt.x;
    cy += infoVertices[i].pt.y;
  }
  cx /= sz;
  cy /= sz;

  centroid = Point2D ((int) round(cx), (int) round(cy));
}


Figure Figure::operator=(Figure f)
{
  for (int i=0; i<3; i++)
  {
	  RGB[i] = f.RGB[i];
    RGBf[i] = f.RGBf[i];
  }
  id = f.id;
	centroid = f.centroid;
	area = f.area;
  vertices = f.vertices;
	infoVertices = f.infoVertices;
  ncomponents = f.ncomponents;
  nvertices = f.nvertices;
  comp = f.comp;
  isIntern = f.isIntern;
  curves = f.curves;
  components = f.components;
  containers = f.containers;
  neighbours = f.neighbours;
  father = f.father;
	qualPtV = f.qualPtV;
  border = f.border;
  regular = f.regular;
  color = f.color;
	description = f.description;
	name = f.name;
  convexity = f.convexity;
	return *this;
}

void Figure::info2vertices(void)
{
  int size = infoVertices.size();
  vertices.resize(size);

  for (int i=0; i<size; i++)
    vertices[i] = infoVertices[i].pt;

}

ostream& operator<<(ostream &os, Figure &f)
{
  if (f.nvertices>0)
  {
    os<<endl<<"Figure's id: "<<f.id<<endl;
    os<<"\tNum vertices: "<<f.nvertices<<endl;
/*
    os<<"\tVertices: ";
    for (unsigned int i=0; i<f.infoVertices.size(); i++)
      os<<f.infoVertices[i]<<" ";
    os<<endl;
*/
    os<<"\tQDescription: ";
    for (unsigned int i=0; i<f.qualPtV.size(); i++)
      os<<f.qualPtV[i]<<" ";
    os<<endl;
    if (f.comp)
    {
      os<<"\tCompound: True - ";
      os<<"Components' id: { ";
      for (unsigned int j = 0; j<f.components.size(); j++)
        os<<f.components[j]->id<<" ";
      os<<"}"<<endl;
    }
    else
      os<<"\tCompound: False"<<endl;
    if (f.isIntern)
    {
      os<<"\tInternal: True - ";
      os<<"Father's id: ";
      os<<f.father->id<<endl;
    }
    else
      os<<"\tInternal: False"<<endl;
    switch(f.curves)
    {
      case 0:
        os<<"\tWithout curves"<<endl;
        break;
      case 1:
        os<<"\tWith curves"<<endl;
        break;
      case 2:
        os<<"\tOnly curves"<<endl;
        break;
    }
    os<<"\tCentroid: "<<f.centroid<<endl;
    os<<"\tArea: "<<f.area<<endl;
    os<<"\tRGB Color: {"<<f.RGB[0]<<", "<<f.RGB[1]<<", "<<f.RGB[2]<<"}"<<endl;
    os<<"\tHSV Color: {"<<f.HSV[0]<<", "<<f.HSV[1]<<", "<<f.HSV[2]<<"}"<<endl;
    os<<"\tHSL Color: {"<<f.HSL[0]<<", "<<f.HSL[1]<<", "<<f.HSL[2]<<"}"<<endl;
    os<<"\tColor: "<<f.color<<endl;
    switch(f.convexity)
    {
      case 0:
        os<<"\tConcave figure"<<endl;
        break;
      case 1:
        os<<"\tConvex figure"<<endl;
        break;
    }
    if (f.regular)
      os<<"\tRegular polygon"<<endl;
    os<<"\t"<<f.description<<endl;
  }


  return os;
}

void Figure::RGBtoHSV(void)
{
	float min, max, delta;
  float r, g, b, h, s, v;

  r = RGBf[0];
  g = RGBf[1];
  b = RGBf[2];

	min = MIN(RGBf);
	max = MAX(RGBf);

	v = max;	// v

	delta = max - min;

	if( max != 0 )
		s = delta / max;	// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		s = 0;
		h = -1;
		return;
	}

  if (max == min)
    h = 0; //Achromatic
  else
  {
    if (r == max)
	    h = (g - b) / delta;		// between yellow & magenta
		if (g == max)
      h = 2 + (b - r) / delta;	// between cyan & yellow
		if (b == max)
      h = 4 + (r - g) / delta;	// between magenta & cyan
  }

	h *= 60;				// degrees
	if(h < 0)
		h += 360;

  HSV[0] = (int) round(h);
  HSV[1] = (int) (s*100);
  HSV[2] = (int) (v*100);
}

void Figure::RGBtoHSL(void)
{
	float min, max, delta;
  float r, g, b, h, s, l;

  r = RGBf[0];
  g = RGBf[1];
  b = RGBf[2];

	min = MIN(RGBf);
	max = MAX(RGBf);

	delta = max - min;

  l = (max + min) / 2;

  if(max == min)
    h = s = 0; // achromatic
  else
  {
    s = l > 0.5 ? delta / (2 - delta) : delta / (max + min);
    if (r == max)
      h = (g - b) / delta;
    if (g == max)
      h = (b - r) / delta + 2;
    if (b == max)
      h = (r - g) / delta + 4;
  }

	h *= 60;				// degrees
	if(h < 0)
		h += 360;

  HSL[0] = (int) round(h);
  HSL[1] = (int) (s*100);
  HSL[2] = (int) (l*100);
}


string Figure::shapeStringDescription(void)
{
  string res = "[";

  if (nvertices > 0)
  {
		name = "NONAME";
		res += "["+name+",";
		if (regular)
			res += "regular,";
		else
			res += "non-regular,";
		switch(convexity)
		{
			case 0:
				res += "concave],";
				break;
			case 1:
				res += "convex],";
				break;
		}
		res += "[";
    for (unsigned int i=0; i<qualPtV.size(); i++)
    {
			res += "[";
			switch (qualPtV[i].shape)
			{
				case 11:
					res += "line-line,";
					break;
				case 12:
					res += "line-curve,";
					break;
				case 21:
					res += "curve-line,";
					break;
				case 22:
					res += "curve-curve,";
					break;
				case 2:
					res += "curvature-point,";
					break;
			}
      		if (qualPtV[i].shape != 2)
		{
			switch (qualPtV[i].angle)
        		{
          			case -2:
            				res += "very_acute,";
            			break;
          			case -1:
            				res += "acute,";
            			break;
          			case 0:
            				res += "right,";
            			break;
          			case 1:
            				res += "obtuse,";
            			break;
          			case 2:
            				res += "very_obtuse,";
            			break;
          			default:
            				res += "NONE,";
            			break;
        	}

		switch(qualPtV[i].size)
        	{
			case -3:
				res += "msh,"; //much_shorter x shorter than half (sth)
			break;
			case -2:
    		    		res += "hl,";  //half_length x half (h)
        		break;
			case -1:
				res += "qsh,"; //quite_shorter x longer than half (lth)
			break;
      			case 0:
        			res += "sl,"; //similar_length x equal (e)
        		break;
      			case 1:
        			res += "ql,"; //quite_longer x shorter than double (std)
        		break;
			case 2:
				res += "dl,";  //double_length x double (d)
			break;
			case 3:
				res += "ml,"; //much_longer x longer than double (ltd)
			break;
      			default:
        			res += "NONE,";
        		break;
		}

		switch(qualPtV[i].convexity)
        	{
          		case 0:
            			res += "concave";
            		break;
          		case 1:
            			res += "convex";
            		break;
        	}
	}
	else
	{
		switch (qualPtV[i].angle)
        	{
			case -2:
				res += "very-plane,";
			break;
          		case -1:
            			res += "plane,";
            		break;
          		case 0:
            			res += "semicircular,";
            		break;
          		case 1:
            			res += "acute,";
            		break;
			case 2:
				res += "very-acute,";
			break;
        	}
        	switch(qualPtV[i].size)
        	{
			case -3:
				res += "msh,"; //much_shorter x shorter than half (sth)
			break;
			case -2:
    		    		res += "hl,";  //half_length x half (h)
        		break;
			case -1:
				res += "qsh,"; //quite_shorter x longer than half (lth)
			break;
      			case 0:
        			res += "sl,"; //similar_length x equal (e)
        		break;
      			case 1:
        			res += "ql,"; //quite_longer x shorter than double (std)
        		break;
			case 2:
				res += "dl,";  //double_length x double (d)
			break;
			case 3:
				res += "ml,"; //much_longer x longer than double (ltd)
			break;
      			default:
        			res += "NONE,";
        		break;
				}
        switch(qualPtV[i].convexity)
        {
          case 0:
            res += "concave";
            break;
          case 1:
            res += "convex";
            break;
        }
      }
			res += "]";
      if (i == qualPtV.size()-1)
        res += "]";
      else
        res += ",";
    }
  }
	res += "]";

  return res;
}

string Figure::shapeStringDescriptionOriginal(void)
{
  string res = "[";

  if (nvertices > 0)
  {
		name = "NONAME";
		res += "["+name+",";
		if (regular)
			res += "regular,";
		else
			res += "non-regular,";
		switch(convexity)
		{
			case 0:
				res += "concave],";
				break;
			case 1:
				res += "convex],";
				break;
		}
		res += "[";
		int temp;
    for (int i=0; i<nqpts; i++)
    {
			res += "[";
      if (qualPtV[i].shape != 2)
			{
				temp = qualPtV[i].angle;
				if (temp < 0)
					res += "acute,";
				else if (temp == 0)
					res += "right,";
				else if (temp > 0)
					res += "obtuse,";
				else
					res += "NONE,";

				temp = qualPtV[i].size;

				if (temp < 0)
					res += "smaller,";
				else if (temp == 0)
					res += "equal,";
				else if (temp > 0)
					res += "bigger,";
				else
					res += "NONE,";

				temp = qualPtV[i].convexity;

				if (temp == 0)
					res += "concave";
				else if (temp == 1)
					res += "convex";
				else
					res += "NONE,";
			}
			else
			{
				temp = qualPtV[i].angle;

				if (temp < 0)
					res += "plane,";
				else if (temp == 0)
					res += "semicircular,";
				else if (temp > 0)
					res += "acute,";
				else
					res += "NONE,";

				temp = qualPtV[i].size;

				if (temp < 0)
					res += "smaller,";
				else if (temp == 0)
					res += "equal,";
				else if (temp > 0)
					res += "bigger,";
				else
					res += "NONE,";

				temp = qualPtV[i].convexity;

				if (temp == 0)
					res += "concave";
				else if (temp == 1)
					res += "convex";
				else
					res += "NONE,";
      }
			res += "]";
      if (i == nqpts-1)
        res += "]";
      else
        res += ",";
    }
  }
	res += "]";

  return res;
}

//Zfalomir: primera versión, todas las caracteristicas de cada figura juntas
string Figure::stringDescription_all(void)
{

  string res = "[ ";

  if (nvertices > 0)
  {
		std::stringstream sstr2;
		sstr2 << id;
		std::string fig_id_str = sstr2.str();
		res += fig_id_str +", ";

		res += name+", ";

		res += color +", ";

		if (regular) res += "regular, ";
		else  res += "irregular, ";

		switch(convexity){
			case 0: res += "concave, "; break;
			case 1: res += "convex, "; break;
		}

		//switch(curves){
		//	case 0: res+="without_curves, "; break;
		//	case 1: res+="with_curves, "; break;
		//	case 2: res+="only_curves, "; break;
		//}

  		//switch (size_wrt_image){
		//	case (none_size_wrt_image): res+= "none,";break;
		//	case (small): res+="small,";break;
		//	case (medium): res+="medium,"; break;
		//	case (large): res+="large,"; break;
		//	default: res+="error,"; break;
    		//}


		//Printing fixed orientation wrt the image
		res+=" [";
    		for (unsigned int i = 0; i < VFixed_Orient_wrt_image.size(); i++){
  			switch (VFixed_Orient_wrt_image[i]){
    				case none_orientation: res+= "none"; break;
    				case _front: res+= "front"; break;
    				case _back: res+= "back"; break;
    				case _left: res+= "left"; break;
    				case _right: res+= "right"; break;
    				case _front_left: res+= "front_left"; break;
    				case _front_right: res+= "front_right"; break;
    				case _back_left: res+= "back_left"; break;
    				case _back_right: res+= "back_right"; break;
				case _centre: res+= "centre"; break;
    				default: res+= "error"; break;
   			 }
			if (i < VFixed_Orient_wrt_image.size()-1) res+= ", ";
		}

		res += "],";

		res += "\n\t\t[";

    //Impresión descripción de la modificación del Modelo de Museros&Escrig
    for (unsigned int i=0; i<qualPtV.size(); i++)
    {
	res += "[";
	switch (qualPtV[i].shape){
		case LINE_LINE: 	res += "line-line,"; break;
		case LINE_CURVE: 	res += "line-curve,"; break;
		case CURVE_LINE: 	res += "curve-line,"; break;
		case CURVE_CURVE: 	res += "curve-curve,"; break;
		case POINT_CURVATURE: 	res += "curvature-point,"; break;
	}

      	if (qualPtV[i].shape != POINT_CURVATURE){

		switch (qualPtV[i].angle){
			case VERY_ACUTE_ANGLE:	res += "very_acute,"; break;
          		case ACUTE_ANGLE: 	res += "acute,"; break;
          		case RIGHT_ANGLE: 	res += "right,"; break;
          		case OBTUSE_ANGLE: 	res += "obtuse,"; break;
			case VERY_OBTUSE_ANGLE:	res += "very_obtuse,"; break;
          		default: 		res += "NONE,"; break;
        	}

	}
	else
	{
		switch (qualPtV[i].angle){
			case VERY_PLANE_CURVE: 	res += "very-plane,"; break;
          		case PLANE_CURVE: 	res += "plane,"; break;
          		case SEMICIRCULAR_CURVE: res += "semicircular,"; break;
          		case ACUTE_CURVE:	res += "acute,"; break;
			case VERY_ACUTE_CURVE:  res += "very-acute,"; break;
		}

	}

	switch(qualPtV[i].size){
		case STH_EDGE: 	res += "sth,"; break;
	      	case H_EDGE: 	res += "h,"; break;
		case LTH_EDGE: 	res += "lth,"; break;
      		case E_EDGE: 	res += "e,"; break;
      		case STD_EDGE: 	res += "std,"; break;
		case D_EDGE: 	res += "d,"; break;
		case LTD_EDGE: 	res += "ltd,"; break;
      		default: 	res += "NONE,"; break;
	}

	switch(qualPtV[i].convexity){
       		case CONCAVE: 	res += "concave"; break;
       		case CONVEX: 	res += "convex"; break;
       	}

      res += "]";

      if (i == qualPtV.size()-1)
        res += "],";
      else
        res += ",";
    }
  }



	//Imprimimos el vector de vecinos: las relaciones topológicas

	res+= "\n\t\t[touching";
	for (unsigned int i = 0; i < neighboursVector.size(); i++){

		std::stringstream sstr;
		sstr << neighboursVector[i];
		std::string id_str = sstr.str();

		res+= ", "+ id_str;
	}
	res+= "]";

	//Imprimimos el tamaño comparado con otras figuras

	res+="\n\t\t[";
    	for (unsigned int i = 0; i < sizeVector_wrt_fig.size(); i++){

		std::stringstream sstr;
		sstr << sizeVector_wrt_fig[i].Fig_id;
		std::string id_str = sstr.str();

		res+= "["+ id_str + ", ";

		switch (sizeVector_wrt_fig[i].size_wrt_Fig_id){
    			case none_size_wrt_figure: res+= "none"; break;
    			case much_smaller: res+= "much_smaller"; break;
    			case half_size: res+= "half_size"; break;
    			case a_bit_smaller: res+= "a_bit_smaller"; break;
    			case similar_size: res+= "similar_size"; break;
    			case a_bit_bigger: res+= "a_bit_bigger"; break;
    			case double_size: res+= "double_size"; break;
    			case much_bigger: res+= "much_bigger"; break;
    			default: res+= "error"; break;
   		 }

		if (i < sizeVector_wrt_fig.size()-1) res+= "],";
		else res+= "]";
	}

	res += "],";


	//Printing fixed orientation wrt other figures
	res+="\n\t\t[";
    	for (unsigned int i = 0; i < VFixed_Orient_wrt_figures.size(); i++){

		std::stringstream sstr;
		sstr << VFixed_Orient_wrt_figures[i].Fig_id;
		std::string id_str = sstr.str();

		res+= "["+ id_str + ", ";

		for (unsigned int f = 0; f < VFixed_Orient_wrt_figures[i].VFixed_orient.size(); f++){

  			switch (VFixed_Orient_wrt_figures[i].VFixed_orient[f]){
    				case none_orientation: res+= "none"; break;
    				case _front: res+= "front"; break;
    				case _back: res+= "back"; break;
    				case _left: res+= "left"; break;
    				case _right: res+= "right"; break;
    				case _front_left: res+= "front_left"; break;
    				case _front_right: res+= "front_right"; break;
    				case _back_left: res+= "back_left"; break;
    				case _back_right: res+= "back_right"; break;
				case _centre: res+= "centre"; break;
    				default: res+= "error"; break;
   			}
			if (f < VFixed_Orient_wrt_figures[i].VFixed_orient.size()-1) res+= ", ";
			else if ( i < VFixed_Orient_wrt_figures.size()-1)
				  res+= "], ";
			     else res+= "]";

		}
	}

	res += "],";

	//Printing relative orientations
	res+="\n\t\t[";
    	for (unsigned int i = 0; i < VRelative_Orientations.size(); i++){

		std::stringstream sstr, sstr2;
		sstr << VRelative_Orientations[i].rs.id_fig_a;
		sstr2 << VRelative_Orientations[i].rs.id_fig_b;
		std::string id_A = sstr.str();
		std::string id_B = sstr2.str();

		res+= "[["+ id_A + ", "+ id_B +"], ";

		for (unsigned int f = 0; f < VRelative_Orientations[i].VRel_orient.size(); f++){

			switch (VRelative_Orientations[i].VRel_orient[f]){
    				case none_rel_orientation: res+= "none"; break;
    				case lf:  res+= "left_front"; break;
    				case sf:  res+= "straight_front"; break;
    				case rf:  res+= "right_front"; break;
    				case l:   res+= "left"; break;
    				case idf: res+= "identical_front"; break;
    				case r:   res+= "right"; break;
    				case lm:  res+= "left_middle"; break;
    				case sm:  res+= "same_middle"; break;
    				case rm:  res+= "right_middle"; break;
    				case ibl: res+= "identical_back_left"; break;
    				case ib:  res+= "identical_back"; break;
    				case ibr: res+= "identical_back_right"; break;
    				case bl:  res+= "back_left"; break;
				case sb:  res+= "straight_back"; break;
    				case br:  res+= "back_right"; break;
    				default:  res+= "error"; break;
    			}

			if (f < VRelative_Orientations[i].VRel_orient.size()-1) res+= ", ";
			else if ( i < VRelative_Orientations.size()-1)
				  res+= "], ";
			     else res+= "]";

		}
	}

	res += "],";

	//Printing compared distances between figures
	res+="\n\t\t[";
    	for (unsigned int i = 0; i < VCompared_distances.size(); i++){

		std::stringstream sstr, sstr2;
		sstr << VCompared_distances[i].Fig_A;
		sstr2 << VCompared_distances[i].Fig_B;
		std::string id_A = sstr.str();
		std::string id_B = sstr2.str();

		res+= "["+ id_A + ", "+ id_B +", ";

		switch (VCompared_distances[i].compared_distance_AwrtB){
    			case none_distance: res+= "none"; break;
    			case closer_than: res+= "closer_than"; break;
    			case nearby: res+= "nearby"; break;
    			case further_than: res+= "further_than"; break;
    			default: res+= "error"; break;
   		}
		if (i < VCompared_distances.size()-1) res+= "],";
		else res+= "]";
	}

	res += "]\n";

  return res;
}



//Caracteristicas por separado
string Figure::stringVisualDescription(void)
{

  string res = "\t[ ";

  if (nvertices > 0){

		std::stringstream sstr2;
		sstr2 << id;
		std::string fig_id_str = sstr2.str();
		res += fig_id_str +", ";

		res += name+", ";

		res += color +", ";

		if (regular) res += "regular, ";
		else  res += "irregular, ";

		switch(convexity){
			case 0: res += "concave, "; break;
			case 1: res += "convex, "; break;
		}

		res += "\n\t\t[Boundary_Shape,\n\t\t\t";
    		//Impresión descripción de la modificación del Modelo de Falomir et al. 2008 (AAAI'2008)
   		for (unsigned int i=0; i<qualPtV.size(); i++)
    		{
			res += "[";
			switch (qualPtV[i].shape){
				case LINE_LINE: 	res += "line-line,"; break;
				case LINE_CURVE: 	res += "line-curve,"; break;
				case CURVE_LINE: 	res += "curve-line,"; break;
				case CURVE_CURVE: 	res += "curve-curve,"; break;
				case POINT_CURVATURE: 	res += "curvature-point,"; break;
			}

     		 	if (qualPtV[i].shape != POINT_CURVATURE){

				switch (qualPtV[i].angle){
					case VERY_ACUTE_ANGLE:	res += "very_acute,"; break;
          				case ACUTE_ANGLE: 	res += "acute,"; break;
          				case RIGHT_ANGLE: 	res += "right,"; break;
          				case OBTUSE_ANGLE: 	res += "obtuse,"; break;
					case VERY_OBTUSE_ANGLE:	res += "very_obtuse,"; break;
          				default: 		res += "NONE,"; break;
        			}

			}
			else
			{
				switch (qualPtV[i].angle){
					case VERY_PLANE_CURVE: 	res += "very-plane,"; break;
      			    		case PLANE_CURVE: 	res += "plane,"; break;
        		  		case SEMICIRCULAR_CURVE: res += "semicircular,"; break;
        		  		case ACUTE_CURVE:	res += "acute,"; break;
					case VERY_ACUTE_CURVE:  res += "very-acute,"; break;
				}

			}

			switch(qualPtV[i].size){
				case STH_EDGE: 	res += "much_shorter,"; break;
			      	case H_EDGE: 	res += "half,"; break;
				case LTH_EDGE: 	res += "a_bit_shorter,"; break;
      				case E_EDGE: 	res += "similar_lenght,"; break;
      				case STD_EDGE: 	res += "a_bit_longer,"; break;
				case D_EDGE: 	res += "double,"; break;
				case LTD_EDGE: 	res += "much_longer,"; break;
      				default: 	res += "NONE,"; break;
			}

			switch(qualPtV[i].convexity){
       				case CONCAVE: 	res += "concave"; break;
       				case CONVEX: 	res += "convex"; break;
       			}

     		 	res += "]";

      			if (i == qualPtV.size()-1)
        			res += "],";
      			else
        			res += ",\n\t\t\t";
    		}
	}


	//Printing fixed orientation of all vertices
	res+=" \n\t\t[Vertices_Orientation, \n\t\t\t";
    	for (unsigned int i = 0; i < VFixed_Orient_vertices.size(); i++){
  		switch (VFixed_Orient_vertices[i]){
    			case none_orientation: res+= "none"; break;
    			case _front: res+= "front"; break;
    			case _back: res+= "back"; break;
    			case _left: res+= "left"; break;
    			case _right: res+= "right"; break;
    			case _front_left: res+= "front_left"; break;
    			case _front_right: res+= "front_right"; break;
    			case _back_left: res+= "back_left"; break;
    			case _back_right: res+= "back_right"; break;
			case _centre: res+= "centre"; break;
    			default: res+= "error"; break;
   		 }
		if (i < VFixed_Orient_vertices.size()-1) res+= ", ";
	}

	res += "], ";



	//Imprimimos el tamaño comparado con otras figuras
	res+="\n\t\t[Relative_Size, \n\t\t\t";
    	for (unsigned int i = 0; i < sizeVector_wrt_fig.size(); i++){

		std::stringstream sstr;
		sstr << sizeVector_wrt_fig[i].Fig_id;
		std::string id_str = sstr.str();

		res+= "["+ id_str + ", ";

		switch (sizeVector_wrt_fig[i].size_wrt_Fig_id){
    			case none_size_wrt_figure: res+= "none"; break;
    			case much_smaller: res+= "much_smaller"; break;
    			case half_size: res+= "half_size"; break;
    			case a_bit_smaller: res+= "a_bit_smaller"; break;
    			case similar_size: res+= "similar_size"; break;
    			case a_bit_bigger: res+= "a_bit_bigger"; break;
    			case double_size: res+= "double_size"; break;
    			case much_bigger: res+= "much_bigger"; break;
    			default: res+= "error"; break;
   		 }

		if (i < sizeVector_wrt_fig.size()-1) res+= "],";
		else res+= "]";
	}

	res += "]\n";
	res += "\t],\n";

  return res;
}


string Figure::stringSpatialDescription(void)
{

  string res = "\t[ ";

  if (nvertices > 0)
  {
		std::stringstream sstr2;
		sstr2 << id;
		std::string fig_id_str = sstr2.str();
		res += fig_id_str +", ";


		//Printing fixed orientation wrt the image
		res+=" [IMG, Completely_inside,  ";
    		for (unsigned int i = 0; i < VFixed_Orient_wrt_image.size(); i++){
  			switch (VFixed_Orient_wrt_image[i]){
    				case none_orientation: res+= "none"; break;
    				case _front: res+= "front"; break;
    				case _back: res+= "back"; break;
    				case _left: res+= "left"; break;
    				case _right: res+= "right"; break;
    				case _front_left: res+= "front_left"; break;
    				case _front_right: res+= "front_right"; break;
    				case _back_left: res+= "back_left"; break;
    				case _back_right: res+= "back_right"; break;
				case _centre: res+= "centre"; break;
    				default: res+= "error"; break;
   			 }
			if (i < VFixed_Orient_wrt_image.size()-1) res+= ", ";
		}

		res += "],\n";

		//Imprimimos el vector de vecinos: las relaciones topológicas

		res += "\t\t[";
		if (neighboursVector.size() > 0){
		   res+= "[touching";
		   for (unsigned int i = 0; i < neighboursVector.size(); i++){

			std::stringstream sstr;
			sstr << neighboursVector[i];
			std::string id_str = sstr.str();

			res+= ", "+ id_str;
		   }
		   res+= "], ";
		}
		if (disjointsVector.size() > 0){
		   res+= "[disjoint";
		   for (unsigned int i = 0; i < disjointsVector.size(); i++){

			std::stringstream sstr;
			sstr << disjointsVector[i];
			std::string id_str = sstr.str();

			res+= ", "+ id_str;
		   }
		   res+= "], ";
		}

		res+= "]\n";

		//Printing fixed orientation wrt other figures
		res+="\t\t[";
    		for (unsigned int i = 0; i < VFixed_Orient_wrt_figures.size(); i++){

			std::stringstream sstr;
			sstr << VFixed_Orient_wrt_figures[i].Fig_id;
			std::string id_str = sstr.str();

			res+= "["+ id_str + ", ";

			for (unsigned int f = 0; f < VFixed_Orient_wrt_figures[i].VFixed_orient.size(); f++){

  				switch (VFixed_Orient_wrt_figures[i].VFixed_orient[f]){
    					case none_orientation: res+= "none"; break;
    					case _front: res+= "front"; break;
    					case _back: res+= "back"; break;
    					case _left: res+= "left"; break;
    					case _right: res+= "right"; break;
    					case _front_left: res+= "front_left"; break;
    					case _front_right: res+= "front_right"; break;
    					case _back_left: res+= "back_left"; break;
    					case _back_right: res+= "back_right"; break;
					case _centre: res+= "centre"; break;
    					default: res+= "error"; break;
   				}
				if (f < VFixed_Orient_wrt_figures[i].VFixed_orient.size()-1) res+= ", ";
				else if ( i < VFixed_Orient_wrt_figures.size()-1)
					  res+= "], ";
				     else res+= "]";

			}
		}

		res += "],";


		if (VRelative_Orientations.size() > 0){
		    //Printing relative orientations
		    res+="\n\t\t[";
    		    for (unsigned int i = 0; i < VRelative_Orientations.size(); i++){

			std::stringstream sstr, sstr2;
			sstr << VRelative_Orientations[i].rs.id_fig_a;
			sstr2 << VRelative_Orientations[i].rs.id_fig_b;
			std::string id_A = sstr.str();
			std::string id_B = sstr2.str();

			res+= "[["+ id_A + ", "+ id_B +"], ";

			for (unsigned int f = 0; f < VRelative_Orientations[i].VRel_orient.size(); f++){

				switch (VRelative_Orientations[i].VRel_orient[f]){
    					case none_rel_orientation: res+= "none"; break;
    					case lf:  res+= "left_front"; break;
    					case sf:  res+= "straight_front"; break;
    					case rf:  res+= "right_front"; break;
   	 				case l:   res+= "left"; break;
    					case idf: res+= "identical_front"; break;
    					case r:   res+= "right"; break;
    					case lm:  res+= "left_middle"; break;
    					case sm:  res+= "same_middle"; break;
    					case rm:  res+= "right_middle"; break;
    					case ibl: res+= "identical_back_left"; break;
    					case ib:  res+= "identical_back"; break;
    					case ibr: res+= "identical_back_right"; break;
    					case bl:  res+= "back_left"; break;
					case sb:  res+= "straight_back"; break;
    					case br:  res+= "back_right"; break;
    					default:  res+= "error"; break;
    				}

				if (f < VRelative_Orientations[i].VRel_orient.size()-1) res+= ", ";
				else if ( i < VRelative_Orientations.size()-1)
					  res+= "], ";
				     else res+= "]";

			}
 		   }
		}

		//res += "],";


		//Printing compared distances between figures
	      	if (VCompared_distances.size() > 0){
			res+="\n\t[";
    			for (unsigned int i = 0; i < VCompared_distances.size(); i++){

				std::stringstream sstr, sstr2;
				sstr << VCompared_distances[i].Fig_A;
				sstr2 << VCompared_distances[i].Fig_B;
				std::string id_A = sstr.str();
				std::string id_B = sstr2.str();

				res+= "["+ id_A + ", "+ id_B +", ";

				switch (VCompared_distances[i].compared_distance_AwrtB){
    					case none_distance: res+= "none"; break;
    					case closer_than: res+= "closer_than"; break;
    					case nearby: res+= "nearby"; break;
    					case further_than: res+= "further_than"; break;
    					default: res+= "error"; break;
   				}
				if (i < VCompared_distances.size()-1) res+= "],";
				else res+= "]";
			}
		}
	}

	res += "]\n";
	res += "\t],\n";

	return res;
}


string Figure::stringSpatialDescription_object_centred(void)
{

  string res = "\t[ ";

  if (nvertices > 0)
  {
		std::stringstream sstr2;
		sstr2 << id;
		std::string fig_id_str = sstr2.str();
		res += fig_id_str +", ";


		//Printing fixed orientation wrt the image
		res+=" [Completely_inside,  ";
    		for (unsigned int i = 0; i < VFixed_Orient_wrt_image.size(); i++){
  			switch (VFixed_Orient_wrt_image[i]){
    				case none_orientation: res+= "none"; break;
    				case _front: res+= "front"; break;
    				case _back: res+= "back"; break;
    				case _left: res+= "left"; break;
    				case _right: res+= "right"; break;
    				case _front_left: res+= "front_left"; break;
    				case _front_right: res+= "front_right"; break;
    				case _back_left: res+= "back_left"; break;
    				case _back_right: res+= "back_right"; break;
				case _centre: res+= "centre"; break;
    				default: res+= "error"; break;
   			 }
			if (i < VFixed_Orient_wrt_image.size()-1) res+= ", ";
		}

		res += "],\n";

		//Imprimimos el vector de vecinos: las relaciones topológicas

		unsigned int fig_id = 0;

		for (unsigned int i = 0; i < topologicalRelVector.size(); i++){


		   if (topologicalRelVector[i] != SAME){


			res += "\t\t[";
			std::stringstream sstr;
			sstr << i;
			std::string id_str = sstr.str();

			res+= id_str + ", ";

			switch (topologicalRelVector[i]){
    					case TOUCHING: res+= "touching"; break;
    					case DISJOINT: res+= "disjoint"; break;
    					case INSIDE: res+= "completedly_inside"; break;
    					case CONTAINER: res+= "container"; break;
    					default: res+= "none"; break;
   			}

			res += ", [";
			for (unsigned int f = 0; f < VFixed_Orient_wrt_figures[fig_id].VFixed_orient.size(); f++){

  				switch (VFixed_Orient_wrt_figures[fig_id].VFixed_orient[f]){
    					case none_orientation: res+= "none"; break;
    					case _front: res+= "front"; break;
    					case _back: res+= "back"; break;
    					case _left: res+= "left"; break;
    					case _right: res+= "right"; break;
    					case _front_left: res+= "front_left"; break;
    					case _front_right: res+= "front_right"; break;
    					case _back_left: res+= "back_left"; break;
    					case _back_right: res+= "back_right"; break;
					case _centre: res+= "centre"; break;
    					default: res+= "error"; break;
   				}
				if (f < VFixed_Orient_wrt_figures[fig_id].VFixed_orient.size()-1) res+= ", ";
				//else if ( fig_id < VFixed_Orient_wrt_figures.size()-1)
					  //res+= "], ";
				     else res+= "]";

			}

			fig_id++;
			res += "],\n";
		    }

		}

		//res += "],";


		if (VRelative_Orientations.size() > 0){
		    //Printing relative orientations
		    res+="\n\t\t[";
    		    for (unsigned int i = 0; i < VRelative_Orientations.size(); i++){

			std::stringstream sstr, sstr2;
			sstr << VRelative_Orientations[i].rs.id_fig_a;
			sstr2 << VRelative_Orientations[i].rs.id_fig_b;
			std::string id_A = sstr.str();
			std::string id_B = sstr2.str();

			res+= "[["+ id_A + ", "+ id_B +"], ";

			for (unsigned int f = 0; f < VRelative_Orientations[i].VRel_orient.size(); f++){

				switch (VRelative_Orientations[i].VRel_orient[f]){
    					//case none_rel_orientation: res+= "none"; break;
					case none_rel_orientation: res+= ""; break;
    					case lf:  res+= "lf"; break;
    					case sf:  res+= "sf"; break;
    					case rf:  res+= "rf"; break;
   	 				case l:   res+= "l"; break;
    					case idf: res+= "idf"; break;
    					case r:   res+= "r"; break;
    					case lm:  res+= "lm"; break;
    					case sm:  res+= "sm"; break;
    					case rm:  res+= "rm"; break;
    					case ibl: res+= "ibl"; break;
    					case ib:  res+= "ibl"; break;
    					case ibr: res+= "ibr"; break;
    					case bl:  res+= "bl"; break;
					case sb:  res+= "sb"; break;
    					case br:  res+= "br"; break;
    					default:  res+= "error"; break;
    				}

				if (f < VRelative_Orientations[i].VRel_orient.size()-1) res+= ", ";
				else if ( i < VRelative_Orientations.size()-1)
					  res+= "], ";
				     else res+= "]";

			}
 		   }
		}

		//res += "],";


		//Printing compared distances between figures
	      	if (VCompared_distances.size() > 0){
			res+="\n\t[";
    			for (unsigned int i = 0; i < VCompared_distances.size(); i++){

				std::stringstream sstr, sstr2;
				sstr << VCompared_distances[i].Fig_A;
				sstr2 << VCompared_distances[i].Fig_B;
				std::string id_A = sstr.str();
				std::string id_B = sstr2.str();

				res+= "["+ id_A + ", "+ id_B +", ";

				switch (VCompared_distances[i].compared_distance_AwrtB){
    					case none_distance: res+= "none"; break;
    					case closer_than: res+= "closer_than"; break;
    					case nearby: res+= "nearby"; break;
    					case further_than: res+= "further_than"; break;
    					default: res+= "error"; break;
   				}
				if (i < VCompared_distances.size()-1) res+= "],";
				else res+= "]";
			}
		}
	}

	res += "]\n";
	res += "\t],\n";

	return res;
}




void Figure::obtaining_all_RS_in_neighboursVector_without_inverses(){

	unsigned int vecino1, vecino2;

	for (unsigned int j = 0; j < neighboursVector.size(); j++){

		vecino1 = neighboursVector[j];

		for (unsigned int k = j; k < neighboursVector.size(); k++){

			vecino2 = neighboursVector[k];

			if (vecino1 != vecino2){

				RS rs(vecino1, vecino2);

				vneighboursRS.push_back(rs);
				cout <<"fig "<< id <<" neighbour RS: " <<rs<<endl;
			}
		}
	}

}

void Figure::obtaining_all_RS_in_neighboursVector_with_inverses(){

	unsigned int vecino1, vecino2;

	for (unsigned int j = 0; j < neighboursVector.size(); j++){

		vecino1 = neighboursVector[j];

		for (unsigned int k = 0; k < neighboursVector.size(); k++){

			vecino2 = neighboursVector[k];

			if (vecino1 != vecino2){

				RS rs(vecino1, vecino2);

				vneighboursRS.push_back(rs);
				cout <<"fig "<< id <<" neighbour RS: " <<rs<<endl;
			}
		}
	}

}

void Figure::set_Size_wrt_Image(QSize_wrt_Image_Type size_tag){

  size_wrt_image = size_tag;

}

//Zfalomir
void Figure::set_slopesVector(){

	double slope = 0.0, inc_y = 0.0, inc_x = 0.0;
	unsigned int j = 0;

	for (unsigned int i=1; i < vertices.size(); i++){

		j = i - 1;
		cout << "i:"<<i<<", j:"<<j<<", ";

		inc_y = (double) (round(vertices[j].getY()) - round(vertices[i].getY()));
		inc_x = (double) (round(vertices[j].getX()) - round(vertices[i].getX()));

		if (inc_x == 0)
			slope = INF_SLOPE;
		else
			slope = inc_y / inc_x;

		Slope s_obj;
		s_obj.set_Slope(i, j, vertices[i], vertices[j], slope);

		cout << "("<<round(vertices[i].getX())<<", "<<round(vertices[i].getY())<<"), (" <<round(vertices[j].getX())<<", "<<round(vertices[j].getY())<<") slope: "<<slope<<endl;
		slopesVector.push_back(s_obj);
	}

	//Falta el último vértice con el vértice 0.
	inc_y = (double)(round(vertices[vertices.size()-1].getY()) - round(vertices[0].getY()));
	inc_x = (double)(round(vertices[vertices.size()-1].getX()) - round(vertices[0].getX()));

	if (inc_x == 0)
		slope = INF_SLOPE;
	else
		slope = inc_y / inc_x;


	Slope s_obj;
	s_obj.set_Slope(0, vertices.size()-1, vertices[0], vertices[vertices.size()-1], slope);


	slopesVector.push_back(s_obj);

	cout << "i:"<<vertices.size()-1 <<", j:0, ("<< round(vertices[vertices.size()-1].getX())<<", "<<round(vertices[vertices.size()-1].getY()) <<"), ("<<round(vertices[0].getX()) <<", "<<round(vertices[0].getY()) <<"), slope: "<<slope<<endl;

}


void Figure::set_regularity(){

	unsigned int num_equal_edges = 0;

	for (unsigned int i = 0; i < qualPtV.size(); i++){

		if ((qualPtV[i].size == E_EDGE)){
			num_equal_edges++;
		}
	}

	if (num_equal_edges == qualPtV.size())
		regular = true;
	else
		regular = false;
}



//Zfalomir
void Figure::set_name(){


  int polycurve = 0;
  int num_points_curvature = 0;
  int same_type_curvature = 1;
  int ant_type_curvature = -11;
  int num_acute_angles = 0;
  int type_of_angle = -11;
  int num_equal_edges = 0;
  int num_right_angles = 0;


  if (curves == 0) //without_curves
  {
    switch(nvertices){
	case 3: name = "triangle"; break;
	case 4: name = "quadrilateral"; break;
	case 5: name = "pentagon";break;
	case 6: name = "hexagon";break;
	case 7: name = "heptagon";break;
	case 8: name = "octagon";break;
	case 9: name = "enneagon";break;
	case 10: name = "decagon";break;
	case 11: name = "undecagon";break;
	case 12: name = "dodecagon";break;
	default: name = "polygon"; break;
    }

    if(nvertices == 3) //Kind_of_triangle
    {
	for (unsigned int i = 0; i < qualPtV.size(); i++){

		if ((qualPtV[i].angle == ACUTE_ANGLE)){
			num_acute_angles++;
		}
		else{
			type_of_angle = qualPtV[i].angle;
		}

		if ((qualPtV[i].size == E_EDGE)){
			num_equal_edges++;
		}

	}

	if (num_acute_angles == 3) name+= "-acute";
 	else if (type_of_angle == RIGHT_ANGLE) name+= "-right";
	else if (type_of_angle == OBTUSE_ANGLE) name+= "-obtuse";

	if (num_equal_edges == 3) name+= "-equilateral";
	else if (num_equal_edges == 2) name+= "-isosceles";
	else name+="-scalene";

    }

    if(nvertices == 4) //Kind_of_quadrilateral
    {
	for (unsigned int i = 0; i < qualPtV.size(); i++){

		if (qualPtV[i].angle == RIGHT_ANGLE){
			num_right_angles++;
		}

		if (qualPtV[i].size == E_EDGE){
			num_equal_edges++;
		}

	}

	if (num_right_angles == 4){
		if (num_equal_edges > 2) name+="-square";
		else name+="-rectangle";
	}
	else{
		if (num_equal_edges == 4) name+="-rhombus";
	}

    }

  }
  else if ((curves == 1) || (curves == 2)) //with_curves
  {
	//mixshape or polycurve?
	polycurve = 1;
	for (unsigned int i = 0; i < qualPtV.size(); i++){
		if ((qualPtV[i].shape == LINE_LINE) || (qualPtV[i].shape == LINE_CURVE) || (qualPtV[i].shape == CURVE_LINE)){
			polycurve = 0;
		}
	}

	if (!polycurve) name = "mixshape";
	else
	{ //circle, ellipse or polycurve?

		if (qualPtV.size() == 4){

			for (unsigned int i = 0; i < qualPtV.size(); i++){

				if ((qualPtV[i].shape == POINT_CURVATURE)){
					num_points_curvature++;

					if (num_points_curvature > 1){
						if (ant_type_curvature != qualPtV[i].angle)
							same_type_curvature = same_type_curvature * 0;
					}
					ant_type_curvature = qualPtV[i].angle;

				}
			}

			if ((same_type_curvature) && (ant_type_curvature == SEMICIRCULAR_CURVE)) name = "circle";
			else if ((same_type_curvature) && (ant_type_curvature != SEMICIRCULAR_CURVE)) name = "ellipse";
			else if (!same_type_curvature) name = "polycurve";
		}
		else  name = "polycurve";
	}
  }


}


int Figure::orientation_in_vector(QFixed_Orientation_Type fOrient){

	int is_in_vector = 0;

	for (unsigned int i = 0; i < VFixed_Orient_wrt_image.size(); i++){
		if (VFixed_Orient_wrt_image[i] == fOrient)
			is_in_vector = 1;
	}


	return is_in_vector;
}

//Si la orientación no está ya en el vector, la añadimos
void Figure::adding_fixed_orient_wrt_image(QFixed_Orientation_Type fOrient){

  if (VFixed_Orient_wrt_image.size() == 0)
	VFixed_Orient_wrt_image.push_back(fOrient);
  else{

	if (!orientation_in_vector(fOrient))
		VFixed_Orient_wrt_image.push_back(fOrient);

  }

}


void Figure::simplifying_fixed_orient_wrt_image(){


	if ((orientation_in_vector(_right)) && (orientation_in_vector(_front)) && (orientation_in_vector(_left)) && (orientation_in_vector(_back))){
		VFixed_Orient_wrt_image.clear();
		VFixed_Orient_wrt_image.push_back(_centre);
	}


}


void Figure::set_distance(unsigned int Fig_id, float distance){

	//distanceVector[Fig_id] = distance;
	distanceVector.push_back(distance);

}
