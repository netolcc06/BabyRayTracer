#ifndef LAMBERTIAN_
#define LAMBERTIAN_

#include "Material.hpp"


class Lambertian : public Material
{

public:

	Lambertian(Vec3<float> a): albedo(a){}

	virtual bool scatter(Ray<float> & r_in, hit_record & rec, Vec3<float> & attenuation, Ray<float> & scattered) const{

		Vec3<float> target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = Ray<float>(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

	Vec3<float> albedo;

};

#endif