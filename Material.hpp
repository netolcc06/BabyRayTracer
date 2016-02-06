#ifndef MATERIAL_
#define MATERIAL_

#include "Hitable.hpp"

class Material
{
public:
	virtual bool scatter(Ray<float> & r_in, hit_record & rec, Vec3<float> & attenuation, Ray<float> & scattered) const = 0;
};



#endif