#include "Engine_Random.h"

template<typename T>
T rand_range(T a, T b)
{
	return a + (T) (((double)(b-a+1))*rand()/(RAND_MAX+1.0));
}

float Random::Range( double a, double b)
{
	return a + (float) ( ((double)(b-a+1))*rand()/(RAND_MAX+1.0));
}
