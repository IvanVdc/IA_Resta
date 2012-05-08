#include "utils.h"

using namespace std;

float MIN(float * v)
{
  float min = 1;
//  int size = sizeof(v)/sizeof(float);
  int size = 3;

  for (int i = 0; i < size; i++)
    min = v[i] < min ? v[i] : min;

  return min;
}

float MAX(float * v)
{
  float max = 0;
//  int size = sizeof(v)/sizeof(float);
  int size = 3;

  for (int i = 0; i < size; i++)
    max = v[i] > max ? v[i] : max;

  return max;
}
