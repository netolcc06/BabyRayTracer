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

	//Vec3f v0v1 = v1_ - v0;
	Vec3<float> v0v1 = v1_ - v0_;
	//Vec3f v0v2 = v2 - v0;
	Vec3<float> v0v2 = v2_ - v0_;
	//Vec3f pvec = dir.crossProduct(v0v2);
	Vec3<float> pvec = Vec3<float>::cross(r.direction(), v0v2);
	//float det = v0v1.dotProduct(pvec);
	float det = Vec3<float>::dot(pvec, v0v1);
	float kEpsilon = 0.00001;

	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (det < kEpsilon) return false;

	// ray and triangle are parallel if det is close to 0
	//if (std::fabs(det) < kEpsilon) return false;

	float invDet = 1 / det;
	
	//Vec3f tvec = orig - v0;
	Vec3<float> tvec = r.origin() - v0_;
	//u = tvec.dotProduct(pvec) * invDet;
	u = Vec3<float>::dot(tvec, pvec) * invDet;
	
	if (u < 0 || u > 1) return false;

	//Vec3f qvec = tvec.crossProduct(v0v1);
	Vec3<float> qvec = Vec3<float>::cross(tvec, v0v1);
	//v = dir.dotProduct(qvec) * invDet;
	v = Vec3<float>::dot(r.direction(), qvec) * invDet;
	if (v < 0 || u + v > 1) return false;

	//std::cout << "u = " << u << "v = "<< v << std::endl; system("pause");

	//t = v0v2.dotProduct(qvec) * invDet;
	t = Vec3<float>::dot(v0v2, qvec) * invDet;

	
	if (t < 0) return false;// std::cout << t << std::endl;

	rec.p = r.point_at_parameter(t);
	/*rec.p = Vec3<float>(t*v0_.x() + u * v1_.x() + v*v2_.x(),
		t*v0_.y() + u * v1_.y() + v*v2_.y(),
		t*v0_.z() + u * v1_.z() + v*v2_.z());//v0_*t + v1_*u + v2_*v;*/
	rec.t = t;
	//if(Vec3<float>::dot(normal, r.direction()))
	rec.normal = normal;
	rec.mat_ptr = material;
	//std::cout << "hits" << std::endl;
	return true;
}

#endif


