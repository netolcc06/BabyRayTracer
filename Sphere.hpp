#ifndef SPHERE_
#define SPHERE_

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"

class Sphere : public Hitable
{
public:
	Sphere(){}
	Sphere(Vec3<float> cen, float r, Material * m): center(cen), radius(r), material(m){};
	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;
	Vec3<float> center;
	float radius;
	Material * material;
};


bool Sphere::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const{

	Vec3<float> oc = r.origin() - center;
	float a = Vec3<float>::dot(r.direction(), r.direction());
	float b = Vec3<float>::dot(oc, r.direction());
	float c = Vec3<float>::dot(oc, oc) - radius*radius;
	float discriminant = b*b - a*c;

	if (discriminant > 0){
		float temp = (-b - sqrt(b*b - a*c)) / a;
		if (temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (1 / radius) *(rec.p - center);
			rec.mat_ptr = material;
			return true;
		}

		temp = (-b + sqrt(b*b - a*c)) / a;
		if (temp < t_max && temp > t_min){
			rec.t = temp;
			rec.p = r.point_at_parameter(rec.t);
			rec.normal = (1 / radius) *(rec.p - center);
			rec.mat_ptr = material;
			return true;
		}
	}
	return false;
}

#endif