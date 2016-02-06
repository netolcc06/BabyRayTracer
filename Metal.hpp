#ifndef METAL_
#define METAL_

#include "Material.hpp"

class Metal : public Material
{
public:
	Metal(Vec3<float> a, float f) : albedo(a), fuzz(f){ if (fuzz < 1) fuzz = f; else fuzz = 1; }
	
	virtual bool scatter(Ray<float> & r_in, hit_record & rec, Vec3<float> & attenuation, Ray<float> & scattered) const{

		Vec3<float> tmp = r_in.direction();
		tmp.normalize();
		Vec3<float> reflected = Vec3<float>::reflect(tmp, rec.normal) + fuzz * random_in_unit_sphere();
		scattered = Ray<float>(rec.p, reflected);
		attenuation = albedo;
		return Vec3<float>::dot(scattered.direction(), rec.normal) > 0 ;
	}

	Vec3<float> albedo;
	float fuzz;
};

#endif