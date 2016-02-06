#ifndef RAY_
#define RAY_

#include "Vec3.hpp"

#include <math.h>

template <typename T>
class Ray
{
public:
	Ray(){}
	Ray(Vec3<T> a, Vec3<T> b):A_(a), B_(b){}
	Vec3<T> origin() const { return A_; }
	Vec3<T> direction() const{ return B_; }
	Vec3<T> point_at_parameter(T t) { return A_ + t*B_; }



	Vec3<T> A_, B_;
};

#endif