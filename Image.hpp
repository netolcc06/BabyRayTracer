#ifndef IMAGE_
#define IMAGE_

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstring>
#include <math.h>

#include "Sphere.hpp"
#include "Hitablelist.hpp"
#include "Camera.hpp"
#include "SimpleRand.hpp"
#include "Lambertian.hpp"
#include "Metal.hpp"
#include "Dieletric.hpp"

float hitSphere(const Vec3<float> center, float radius, const Ray<float> & r){

	Vec3<float> oc = r.origin() - center;
	float a = Vec3<float>::dot(r.direction(), r.direction());
	float b = 2.0 * Vec3<float>::dot(oc, r.direction());
	float c = Vec3<float>::dot(oc, oc) - radius * radius;
	float discriminant = b*b - 4*a*c;

	if (discriminant < 0) return -1.0;
	else
	{
		return (-b - sqrt(discriminant))/(2.0*a);
	}
	return (discriminant > 0);
	
}


Vec3<float> color(Ray<float> & r, Hitable * world, int depth){

	hit_record rec;

	if (world->hit(r, 0.001, 2000000.0f, rec)){
		Ray<float> scattered;
		Vec3<float> attenutation;

		if (depth<50 && rec.mat_ptr->scatter(r, rec, attenutation, scattered)){
			return attenutation*color(scattered, world, depth+1);
		}
		else{
			return Vec3<float>(0.0,0.0,0.0);
		}
	}
	else{
		Vec3<float> unit_direction = r.direction(); unit_direction.normalize();
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3<float>(1.0, 1.0, 1.0) + t*Vec3<float>(0.5, 0.7, 1.0);
	}

	/*if (world->hit(r, 0.0, 20000000.0f, rec)){
		Vec3<float> target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5* color(Ray<float>(rec.p, target-rec.p), world);
		//return 0.5* Vec3<float>(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else
	{
		Vec3<float> unit_direction = r.direction(); unit_direction.normalize();
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t)*Vec3<float>(1.0, 1.0, 1.0) + t*Vec3<float>(0.5, 0.7, 1.0);
	}*/
}

Hitable *random_scene(){
	int n = 500;
	Hitable **list = new Hitable*[n+1];
	list[0] = new Sphere(Vec3<float>(0,-1000,0), 1000, new Lambertian(Vec3<float>(0.5,0.5,0.5)));

	int i = 1;
	
	for (int a = -11; a < 11; a++){
		for (int b = -11; b < 11; b++){
			float choose_mat = Rand();
			Vec3<float> center(a+0.9*Rand(), 0, b+0.9*Rand());

			if (choose_mat < 0.8){
				list[i++] = new Sphere(center, 0.2, new Lambertian(Vec3<float>(Rand()*Rand(), Rand()*Rand(), Rand()*Rand())));
			}
			else if (choose_mat < 0.95){
				list[i++] = new Sphere(center, 0.2, new Metal(Vec3<float>(0.5*(1+Rand()), 0.5*(1+Rand()), 0.5*(1+Rand())), 0.5*Rand()));
			}
			else{
				list[i++] = new Sphere(center, 0.2, new Dieletric(1.5));
			}
		}
	}

	list[i++] = new Sphere(Vec3<float>(0,1,0), 1.0, new Dieletric(1.5));
	list[i++] = new Sphere(Vec3<float>(-4, 1, 0), 1.0, new Lambertian(Vec3<float>(0.4,0.2,0.1)));
	list[i++] = new Sphere(Vec3<float>(0, 1, 0), 1.0, new Metal(Vec3<float>(0.7, 0.6, 0.5), 0.0));

	return new Hitable_list(list, i);
}

template <typename T>
class Image
{
	public:
		Image(int w = 360, int h = 240):width_(w), height_(h){
			data_ = new float[width_*height_];
			memset(data_, 0, sizeof(T)*width_*height_);
		}
		~Image(){ delete[] data_; }
		T getPixel(int i, int j){ return data_[i*width_ + j]; }
		void setPixel(T value, int i, int j){ data_[i*width_ + j] = value; }
		
		void saveImage(std::string filename){
			std::ofstream file;
			file.open(filename);

			file << "P3" << std::endl;
			file << width_ << " " << height_ << std::endl;
			file << "255" << std::endl;

			Hitable *list[5];
			//float R = cos(M_PI / 4);
			list[0] = new Sphere(Vec3<float>(-1.5,0.0,-1.0), 0.5, new Lambertian(Vec3<float>(0.1,0.2,0.5)));
			list[1] = new Sphere(Vec3<float>(1, -100.5, -1.0), 100, new Lambertian(Vec3<float>(0.8, 0.8, 0)));
			list[2] = new Sphere(Vec3<float>(1.5, 0.0, -1.0), 0.5, new Metal(Vec3<float>(0.8, 0.6, 0.2),1.0));
			list[3] = new Sphere(Vec3<float>(0.0, 0.0, -1.0), 0.5, new Dieletric(1.5));
			list[4] = new Sphere(Vec3<float>(0.0, 0.0, -1.0), -0.5, new Dieletric(1.5));
			//list[4] = new Sphere(Vec3<float>(-1.0, 0.0, -5.0), 3.5, new Lambertian(Vec3<float>(0.6, 0.4, 0.5)));
			//list[5] = new Sphere(Vec3<float>(-1.0, 0.0, -1.0), 0.5, new Dieletric(10.5));

			Hitable * world = new Hitable_list(list, 5);
			//Hitable *world = random_scene();

			Vec3<float> lookfrom(0.0, 0.0, 1.0), lookat(0.0, 0.0, -1.0);
			float dist_to_focus = (lookfrom - lookat).length();
			float aperture = 2.0;

			Camera cam(lookfrom, lookat,Vec3<float>(0,1,0), 60, float(width_/height_));
			int ns = 100;
			for (int i = height_-1; i >= 0; i--){
				for (int j = 0; j < width_; j++){

					Vec3<float> col(0.0, 0.0, 0.0);
					for (int s = 0; s < ns; s++)
					{
						float u = float(i + Rand()) / float(height_);
						float v = float(j + Rand()) / float(width_);

						Ray<float> r = cam.getRay(u, v);
						Vec3<float> p = r.point_at_parameter(2.0);
						col += color(r, world, 0);
					}

					float n = float(ns);
					col /= n;
					col = Vec3<float>(sqrt(col.x()), sqrt(col.y()), sqrt(col.z()));
					int ir = int(255.99*col.x()), ig = int(255.99*col.y()), ib = int(255.99*col.z());

					file << ir << " " << ig << " " << ib << endl;
				}
			}
			file.close();
		}

private:
	
	T * data_;
	int width_, height_;
};



#endif