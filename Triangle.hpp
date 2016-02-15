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
	Triangle(Vec3<float> v0, Vec3<float> v1, Vec3<float> v2, Material * m) :v0_(v0), v1_(v1), v2_(v2) {
		material = m;
		normal = Vec3<float>::cross(v1_ - v0_, v2_ - v0_);

		//normal = Vec3<float>(normal.x(), normal.y(), -normal.z());

	}

	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;
	Vec3<float> v0_, v1_, v2_;
	Material * material;
	Vec3<float> normal;
};


bool Triangle::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {


	float thit, u, v;


	float area2 = normal.length();
	float denom = Vec3<float>::dot(normal, normal);

	float NdotRayDirection = Vec3<float>::dot(normal, r.direction());
	if (std::fabs(NdotRayDirection) < 0.0001) // almost 0 
		return false; // parallel

	float d = Vec3<float>::dot(normal, v0_);


	thit = -(Vec3<float>::dot(normal, r.origin()) + d) / NdotRayDirection;

	//std::cout << "chega [0]" << std::endl; system("pause");

	if (thit < 0) return false;

	//std::cout << "chega [1]" << std::endl; system("pause");


	Vec3<float> P = r.origin() + thit*r.direction();

	Vec3<float> C;

	Vec3<float> edge0 = v1_ - v0_;
	Vec3<float> vp0 = P - v0_;
	C = Vec3<float>::cross(edge0, vp0);
	if (Vec3<float>::dot(normal, C) < 0) return false;


	Vec3<float> edge1 = v2_ - v1_;
	Vec3<float> vp1 = P - v1_;
	C = Vec3<float>::cross(edge1, vp1);
	if ((u = Vec3<float>::dot(normal, C)) < 0) return false;


	Vec3<float> edge2 = v0_ - v2_;
	Vec3<float> vp2 = P - v2_;
	C = Vec3<float>::cross(edge2, vp2);
	if ((v = Vec3<float>::dot(normal, C)) < 0) return false;

	//std::cout << "chega [4]" << std::endl; system("pause");

	u /= denom; v /= denom;

	rec.t = thit;
	rec.p = r.point_at_parameter(thit);
	rec.normal = normal;
	//std::cout << "normal = " << rec.normal.x() << " " << rec.normal.y() << " " << rec.normal.z() << std::endl;
	//std::cout << "normal = " << rec.normal.x() << " " << rec.normal.y() << " " << rec.normal.z() << std::endl;
	//std::cout << "normal = " << rec.normal.x() << " " << rec.normal.y() << " " << rec.normal.z() << std::endl;
	//system("pause");


	return true;
}

#endif


