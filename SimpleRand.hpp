#ifndef SIMPRAND_
#define SIMPRAND_

#include <cstdlib>

float Rand(){
	
	float rt = 0.0;
	rt = (float)(rand() % 1000);
	rt /= 1000;

	return rt;
}

#endif