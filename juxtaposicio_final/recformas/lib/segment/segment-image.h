#include <cstdlib>

#include "image.h"
#include "misc.h"
#include "filter.h"
#include "segment-graph.h"

using namespace std;

rgb random_rgb(void);

// dissimilarity measure between pixels
static inline float diff(image<float> * r, image<float> *g, image<float> *b, int x1, int y1, int x2, int y2){
  return sqrt(square(imRef(r, x1, y1)-imRef(r, x2, y2)) +	
	      square(imRef(g, x1, y1)-imRef(g, x2, y2)) +	
	      square(imRef(b, x1, y1)-imRef(b, x2, y2)));	
}		

image<rgb> * segment_image(image<rgb> * im, float sigma, float c, int min_size, int *num_ccs);


