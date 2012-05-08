#include "shapePt.h"


using namespace std;

shapePt::shapePt(void)
{
  shape = -1;
  pt.x = -1;
  pt.y = -1;
}

shapePt::shapePt(Point2D p, int s)
{
  pt = p;
  shape = s;
}

shapePt shapePt::operator=(shapePt p)
{
	pt = p.pt;
	shape = p.shape;
	return *this;
}


bool shapePt::operator==(shapePt &p)
{
  if((p.pt == pt) && (p.shape == shape))
    return true;
  return false;
}

bool shapePt::operator!=(shapePt &p)
{
  if((p.pt != pt) || (p.shape != shape))
    return true;
  return false;
}

ostream& operator<<(ostream &os, shapePt &p)
{
  os<<p.pt<<endl;
//modificat juxtaposicio
  return os;
}


