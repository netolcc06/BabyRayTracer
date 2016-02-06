#ifndef HITABLE_
#define HITABLE_

#include "Vec3.hpp"
#include "Ray.hpp"
//#include "Material.hpp"

class Material;

struct hit_record
{
	float t;
	Vec3<float> p;
	Vec3<float> normal;
	Material * mat_ptr;

};

class Hitable
{
public:
	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const = 0;
};

#endif