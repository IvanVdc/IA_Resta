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
