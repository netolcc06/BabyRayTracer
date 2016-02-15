#ifndef VEC3_
#define VEC3_

#include <math.h>
#include <stdlib.h>
#include <iostream>

#include "SimpleRand.hpp"

#define M_PI 3.14159

using namespace std;


float Schlick(float cosine, float ref_idx){
	float r0 = (1 - ref_idx) / (1+ref_idx);
	r0 *= r0;
	return r0 + (1 - r0)*pow((1-cosine), 5);
}

template <typename T>
class Vec3
{
public:
	Vec3(){}
	Vec3(T x, T y, T z):x_(x), y_(y), z_(z){}
	~Vec3(){}

	Vec3(const Vec3<T> & other){
		this->x_ = other.x();
		this->y_ = other.y();
		this->z_ = other.z();
	}

	void setX(T x){ x_ = x; } void setY(T y){ y_ = y; } void setZ(T z){ z_ = z; }
	void print(){ std::cout << x_ << " " << y_ << " " << z_ << std::endl; }
	
	inline T x() const { return x_; }
	inline T y() const { return y_; }
	inline T z() const { return z_; }
	inline T r() const { return x_; }
	inline T g() const { return y_; }
	inline T b() const { return z_; }

	inline Vec3<T> & operator+( ) const {
		return *this; 
	}

	inline Vec3<T> operator-() const {
		return Vec3(-this->x_, -this->y_, -this->z_);
	}

	inline Vec3<T> operator+(const Vec3<T> & rhs) const{

		return Vec3<T>(this->x_ + rhs.x(), this->y_ + rhs.y(), this->z_ + rhs.z()); 
	}

	inline Vec3<T>  operator-(const Vec3<T> & rhs) const {
		return Vec3<T>(this->x_ - rhs.x(), this->y_ - rhs.y(), this->z_ - rhs.z()); 
	}

	inline Vec3<T>  operator*(const Vec3<T> & rhs) const {
		return Vec3<T>(this->x_ * rhs.x(), this->y_ * rhs.y(), this->z_ * rhs.z());
	}

	inline Vec3<T>  operator/(const Vec3<T> & rhs) const {
		return Vec3<T>(this->x_ / rhs.x(), this->y_ / rhs.y(), this->z_ / rhs.z());
	}

	inline Vec3<T> & operator+=(const Vec3<T> & rhs){
		this->x_ += rhs.x();	this->y_ += rhs.y(); this->z_ += rhs.z();
		return *this;
	}

	inline Vec3<T> & operator-=(const Vec3<T> & rhs){
		this->x_ -= rhs.x();	this->y_ -= rhs.y(); this->z_ -= rhs.z();
		return *this;
	}

	inline Vec3<T> & operator*=(const Vec3<T> & rhs){
		this->x_ = this->x_ * rhs.x(); this->y_ = this->y_ * rhs.y(); this->z_ = this->z_ *rhs.z();
		return *this;
	}

	inline Vec3<T> & operator/=(T rhs){
		this->x_ = this->x_ / rhs; this->y_ = this->y_ / rhs; this->z_ = this->z_ /rhs;
		return *this;
	}

	inline friend Vec3<T> operator*(T lhs, Vec3<T> & rhs){
		return Vec3<T>(rhs.x()*lhs, rhs.y()*lhs, rhs.z()*lhs);
	}

	inline T length() const { return sqrt(x_*x_ + y_*y_ + z_*z_); }
	inline T squared_length() const { return x_*x_ + y_*y_ + z_*z_; }
	
	inline void normalize(){
		T l = length();
		this->x_ = this->x_ / l; this->y_ = this->y_ / l; this->z_ = this->z_ / l;
	}	


	static inline T dot(const Vec3<T> & v1, const Vec3<T> & v2){
		return v1.x()*v2.x() + v1.y()*v2.y() + v1.z()*v2.z();
	}

	static inline Vec3<T> cross(const Vec3<T> & v1, const Vec3<T> & v2){
		return Vec3<T>(v1.y()*v2.z() - v1.z()*v2.y(),
			-(v1.x()*v2.z() - v1.z()*v2.x()),
			v1.x()*v2.y() - v1.y() * v2.x());
	}

	static inline Vec3<T> reflect(Vec3<T> & v, Vec3<T> & n){
		return v - 2 * dot(v, n)*n;
	}

	static inline bool refract(Vec3<T> & v, Vec3<T> & n, float ni_over_nt, Vec3<T> & refracted){
		Vec3<T> uv = v; uv.normalize();
		Vec3<T> un = n; un.normalize();
	
		float dt = Vec3<T>::dot(uv, un);
		float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1-dt*dt);

		if (discriminant > 0){
			refracted = ni_over_nt*(uv - dt*un) - sqrt(discriminant)*un;
			return true;
		}
		else return false;
	}

private:
	T x_, y_, z_;
};


Vec3<float> random_in_unit_sphere(){
	Vec3<float> p;

	float theta = 2 * 3.14 * Rand();
	float phi = acos(1 - 2 * Rand());
	float x = sin(phi) * cos(theta);
	float y = sin(phi) * sin(theta);
	float z = cos(phi);

	return Vec3<float>(x, y, z);
}

Vec3<float> random_in_unit_disk(){
	Vec3<float> p;

	float theta = 2 * 3.14 * Rand();
	float phi = acos(1 - 2 * Rand());
	float x = sin(phi) * cos(theta);
	float y = sin(phi) * sin(theta);
	float z = 0;

	return Vec3<float>(x, y, z);
}



#endif