#include "QPoint.h"


using namespace std;

QPoint::QPoint(void)
{
  shape = 101;
  angle = 101;
  convexity = 101;
  size = 101;
}

QPoint::QPoint(Point2D p, int sp, int a, int c, int sz)
{
  pt = p;
  shape = sp;
  angle = a;
  convexity = c;
  size = sz;
}


QPoint::QPoint(string s)
{

    const string delimiters = ",";
    vector<string> tokens;


    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = s.find_first_of(delimiters, lastPos);

    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = s.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = s.find_first_of(delimiters, lastPos);
    }
	//cout <<"|"<<tokens[0]<<"|"<<tokens[1]<<"|"<<tokens[2]<<"|"<<tokens[3]<<"|"<<endl;

			if (tokens[0]=="line-line"){
				shape=11;
			}
			else
			   if (tokens[0]=="line-curve"){
				shape=12;
			}
			else
			   if (tokens[0]=="curve-line"){
				shape=21;
			}
			else
			   if (tokens[0]=="curve-curve"){
				shape=22;
			}
			else
			   if (tokens[0]=="curvature-point"){
				shape=2;
			}

      		if (shape != 2)
		{

			if (tokens[1]=="very-acute"){
				angle=-2;
			}
			else
			   if (tokens[1]=="acute"){
				angle=-1;
			}
			else
			   if (tokens[1]=="right"){
				angle=0;
			}
			else
			   if (tokens[1]=="obtuse"){
				angle=1;
			}
			else
			   if (tokens[1]=="very-obtuse"){
				angle=2;
			}
			else
			   if (tokens[1]=="NONE"){
				angle=100;
			}



			if (tokens[2]=="msh"){
				size=-3;
			}
			else
			   if (tokens[2]=="hl"){
				size=-2;
			}
			else
			   if (tokens[2]=="qsh"){
				size=-1;
			}
			else
			   if (tokens[2]=="sl"){
				size=0;
			}
			else
			   if (tokens[2]=="ql"){
				size=1;
			}
			else
			   if (tokens[2]=="dl"){
				size=2;
			}
			else
			   if (tokens[2]=="ml"){
				size=3;
			}
			else
			   if (tokens[2]=="NONE"){
				size=100;
			}


			if (tokens[3]=="concave"){
				convexity=0;
			}
			else
			   if (tokens[3]=="convex"){
				convexity=1;
			}



	}
	else
	{

			if (tokens[1]=="very-plane"){
				angle=-2;
			}
			else
			   if (tokens[1]=="plane"){
				angle=-1;
			}
			else
			   if (tokens[1]=="semicircular"){
				angle=0;
			}
			else
			   if (tokens[1]=="acute"){
				angle=1;
			}
			else
			   if (tokens[1]=="very-acute"){
				angle=2;
			}




			if (tokens[2]=="msh"){
				size=-3;
			}
			else
			   if (tokens[2]=="hl"){
				size=-2;
			}
			else
			   if (tokens[2]=="qsh"){
				size=-1;
			}
			else
			   if (tokens[2]=="sl"){
				size=0;
			}
			else
			   if (tokens[2]=="ql"){
				size=1;
			}
			else
			   if (tokens[2]=="dl"){
				size=2;
			}
			else
			   if (tokens[2]=="ml"){
				size=3;
			}
			else
			   if (tokens[2]=="NONE"){
				size=100;
			}


			if (tokens[3]=="concave"){
				convexity=0;
			}
			else
			   if (tokens[3]=="convex"){
				convexity=1;
			}


      }






  pt = Point2D(0, 0);
  /*
  shape = tokens[0];
  angle = tokens[1];
  convexity = tokens[3];
  size = ""//falta;*/
}



QPoint QPoint::operator=(QPoint p)
{
	pt = p.pt;
  shape = p.shape;
  angle = p.angle;
  convexity = p.convexity;
  size = p.size;
  return *this;
}


bool QPoint::operator==(QPoint &p)
{
  if((p.pt == pt) && (p.shape == shape) && (p.angle == angle) && (p.convexity == convexity) && \
      (p.size == size))
    return true;
  else
    return false;
}

ostream& operator<<(ostream &os, QPoint &p)
{
  os<<"{"<<p.pt<<" ";
  if (p.shape == 2)
  {
    os<<"curvature-point ";
    switch(p.angle)
    {
			case -2:
				os<<"[very-plane,";
				break;
      case -1:
        os<<"[plane,";
        break;
      case 0:
        os<<"[semicircular,";
        break;
      case 1:
        os<<"[acute,";
        break;
			case 2:
				os<<"[very-acute,";
				break;
      default:
        os<<"[NONE,";
        break;
    }
    switch(p.convexity)
    {
      case 0:
        os<<"concave,";
        break;
      case 1:
        os<<"convex,";
        break;
      default:
        os<<"NONE,";
        break;
    }
    switch(p.size)
    {
			case -3:
				os<<"sth]";
				break;
      case -2:
        os<<"h]";
        break;
			case -1:
				os<<"lth]";
				break;
      case 0:
        os<<"e]";
        break;
      case 1:
        os<<"std]";
        break;
			case 2:
				os<<"d]";
				break;
			case 3:
				os<<"ltd]";
				break;
      default:
        os<<"NONE]";
        break;
    }
  }
  else
  {
    switch(p.shape)
    {
      case 11:
        os<<"line-line ";
        break;
      case 12:
        os<<"line-curve ";
        break;
      case 21:
        os<<"curve-line ";
        break;
      case 22:
        os<<"curve-curve ";
        break;
      default:
        os<<"NONE ";
        break;
    }

    switch(p.angle)
    {
      case -1:
        os<<"[acute,";
        break;
      case 0:
        os<<"[right,";
        break;
      case 1:
        os<<"[obtuse,";
        break;
      default:
        os<<"[NONE,";
        break;
    }
    switch(p.convexity)
    {
      case 0:
        os<<"concave,";
        break;
      case 1:
        os<<"convex,";
        break;
      default:
        os<<"NONE,";
        break;
    }
    switch(p.size)
    {
			case -3:
				os<<"sth]";
				break;
      case -2:
        os<<"h]";
        break;
			case -1:
				os<<"lth]";
				break;
      case 0:
        os<<"e]";
        break;
      case 1:
        os<<"std]";
        break;
			case 2:
				os<<"d]";
				break;
			case 3:
				os<<"ltd]";
				break;
      default:
        os<<"NONE]";
        break;
    }
	}
  os<<"}";
  return os;
}

bool QPoint::QComparision(QPoint *p)
{
  if((p->shape == shape) && (p->angle == angle) && (p->convexity == convexity) && \
      (p->size == size))
    return true;
  else
    return false;
}
