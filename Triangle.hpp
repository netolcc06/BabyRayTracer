#ifndef TRIANGLE_
#define TRIANGLE_

#include <stdlib.h>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"

class Triangle : public Hitable
{
public:
	Triangle() {}
	Triangle(Vec3<float> v0, Vec3<float> v1, Vec3<float> v2, Material * m) :v0_(v0), v1_(v1), v2_(v2), material(m) {
		normal = Vec3<float>::cross(v1_ - v0_, v2_ - v0_);

		//normal = Vec3<float>(-normal.x(), -normal.y(), -normal.z());

	}

	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;

	Vec3<float> v0_, v1_, v2_;
	Material * material;
	Vec3<float> normal;
};


bool Triangle::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {


	float thit, t, u, v;

	Vec3<float> v0v1 = v1_ - v0_;
	Vec3<float> v0v2 = v2_ - v0_;
	
	Vec3<float> pvec = Vec3<float>::cross(r.direction(), v0v2);
	
	float det = Vec3<float>::dot(pvec, v0v1);
	float kEpsilon = 0.00001;

	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;

	float invDet = 1 / det;
	
	Vec3<float> tvec = r.origin() - v0_;
	u = Vec3<float>::dot(tvec, pvec) * invDet;
	
	if (u < 0 || u > 1) return false;

	Vec3<float> qvec = Vec3<float>::cross(tvec, v0v1);
	v = Vec3<float>::dot(r.direction(), qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	t = Vec3<float>::dot(v0v2, qvec) * invDet;

	
	if (t < 0) return false;// std::cout << t << std::endl;

	rec.p = r.point_at_parameter(t);

	rec.t = t;
	rec.normal = normal;
	rec.mat_ptr = material;
	
	return true;
}

#endif


