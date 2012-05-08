#include "Point2D.h"


using namespace std;

Point2D::Point2D(void)
{
	x=0;
	y=0;
}

Point2D::Point2D(double ix, double iy)
{
  x = ix;
  y = iy;
}

double Point2D::modulo()
{
  return sqrt(x*x + y*y);
}

Point2D Point2D::operator=(Point2D p)
{
	x = p.x;
	y = p.y;
	return *this;
}

Point2D Point2D::operator-(Point2D &p)
{
  Point2D r;
  r.x = x - p.getX();
  r.y = y - p.getY();
  return r;
}

Point2D Point2D::operator+(Point2D &p)
{
  Point2D r;
  r.x = x + p.getX();
  r.y = y + p.getY();
  return r;
}

Point2D Point2D::operator*(Point2D &p)
{
  Point2D producto;
  producto.x=x*p.getX();
  producto.y=y*p.getY();
  return producto;
}

Point2D Point2D::operator-=(Point2D &p)
{
  x -= p.getX();
  y -= p.getY();
  return *this;
}

Point2D Point2D::operator+=(Point2D &p)
{
  x += p.getX();
  y += p.getY();
  return *this;
}

Point2D Point2D::operator*=(Point2D &p)
{
  x *= p.getX();
  y *= p.getY();
  return *this;
}

//bool Point2D::operator==(Point2D &p)
//{
//  if((p.getX() == x) && (p.getY() == y))
//  {
//    return true;
//  }
//  return false;
//}

bool Point2D::operator==(Point2D &p)
{
  return ((p.x == x) && (p.y == y));
}

bool Point2D::operator!=(Point2D &p)
{
  return ((p.x != x) || (p.y != y));
}

ostream& operator<<(ostream &os, Point2D &p)
{
	int x = (int) p.x;
	int y = (int) p.y;
	
  return os<<x<<" , "<<y;
}

/*
Point2D Point2D::menos(Point2D &p)
{
  Point2D r;
  r.x = x - p.getX();
  r.y = y - p.getY();
  return r;
}

Point2D Point2D::mas(Point2D &p)
{
  Point2D r;
  r.x = x + p.getX();
  r.y = y + p.getY();
  return r;
}

Point2D Point2D::producto(Point2D &p)
{
  Point2D producto;
  producto.x=x*p.getX();
  producto.y=y*p.getY();
  return producto;
}
*/

Point2D Point2D::productoEscalar(double p)
// Producto por un escalar.
{
  Point2D producto;
  producto.x=x*p;
  producto.y=y*p;
  return producto;
}

Point2D Point2D::vectorUnitario()
{
  Point2D vectoru;
  vectoru.x = x/modulo();
  vectoru.y = y/modulo();
  return vectoru;
}

/*
Point2D Point2D::round()
{
  double aux_x = x*100;
  aux_x = round(aux_x);
  aux_x = aux_x/100;

  double aux_y = y*100;
  aux_y = round(aux_y);
  aux_y = aux_y/100;

  Point2D p(aux_x, aux_y);
  return p;
}


bool Point2D::equals(Point2D &c)
{
  if((c.getX() == x) && (c.getY() == y))
  {
    return true;
  }
  return false;
}
*/

double Point2D::moduloProductoVectorial(Point2D &p)
{
	return fabs(x*p.getY()-y*p.getX());
}

int Point2D::getX(void)
{
  return (int)round(x);
}

int Point2D::getY(void)
{
  return (int)round(y);
}
