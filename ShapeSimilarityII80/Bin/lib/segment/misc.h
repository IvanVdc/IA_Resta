/* random stuff */

#ifndef MISC_H
#define MISC_H

#include <cmath>
#include <iostream>
#include <cstdio>

//#include "Point2D.h"

#ifndef M_PI
#define M_PI 3.141592653589793
#endif

#ifndef DIST_ZERO
#define DIST_ZERO(r, g, b) (double) sqrt(r*r + g*g + b*b)
#endif

using namespace std;

typedef unsigned char uchar;

typedef struct { uchar r, g, b; } rgb;

inline bool operator==(const rgb &a, const rgb &b) {
  return ((a.r == b.r) && (a.g == b.g) && (a.b == b.b));
}

inline bool operator<(const rgb &a, const rgb &b) {
  return DIST_ZERO(a.r, a.g, a.b) < DIST_ZERO(b.r, b.g, b.b);
}

inline bool operator>(const rgb &a, const rgb &b) {
  return DIST_ZERO(a.r, a.g, a.b) > DIST_ZERO(b.r, b.g, b.b);
}

inline bool operator<=(const rgb &a, const rgb &b) {
  return DIST_ZERO(a.r, a.g, a.b) <= DIST_ZERO(b.r, b.g, b.b);
}

inline bool operator>=(const rgb &a, const rgb &b) {
  return DIST_ZERO(a.r, a.g, a.b) >= DIST_ZERO(b.r, b.g, b.b);
}

inline bool operator!=(const rgb &a, const rgb &b) {
  return ((a.r != b.r) || (a.g != b.g) || (a.b != b.b));
}

inline ostream &operator<<(ostream &os, rgb &c) {
	char cad[16];
	sprintf(cad, "(%u, %u, %u)", c.r, c.g, c.b);
	return (os<<cad);
}

template <class T>
inline T abs(const T &x) { return (x > 0 ? x : -x); };

template <class T>
inline int sign(const T &x) { return (x >= 0 ? 1 : -1); };

template <class T>
inline T square(const T &x) { return x*x; };

template <class T>
inline T bound(const T &x, const T &min, const T &max) {
  return (x < min ? min : (x > max ? max : x));
}

template <class T>
inline bool check_bound(const T &x, const T&min, const T &max) {
  return ((x < min) || (x > max));
}

inline int vlib_round(float x) { return (int)(x + 0.5F); }

inline int vlib_round(double x) { return (int)(x + 0.5); }

inline double gaussian(double val, double sigma) {
  return exp(-square(val/sigma)/2)/(sqrt(2*M_PI)*sigma);
}

#endif
