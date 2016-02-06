#ifndef CAMERA_
#define CAMERA_

#include "Ray.hpp"

class Camera
{
public:
	Camera(Vec3<float> lookfrom, Vec3<float> looakat, Vec3<float> vup ,float vfov, float aspect){//vfov top to bottom in degrees

		float theta = vfov*M_PI / 180;
		float half_height = tan(theta/2);
		float half_width = aspect * half_height;
		origin = lookfrom;
		w = lookfrom - looakat; w.normalize();
		u = Vec3<float>::cross(vup, w); u.normalize();
		v = Vec3<float>::cross(w, u);
		//lower_left_corner = origin - half_width*focus_dist*u - half_height*focus_dist*v - focus_dist*w;
		lower_left_corner = Vec3<float>(-half_width, -half_height, -1.0);
		lower_left_corner = origin - half_width*u - half_height*v-w;
		horizontal = 2.0*half_width*u;
		vertical = 2.0*half_height*v;
		
	}
	
	Ray<float> getRay(float s, float t){ 
		return Ray<float>(origin, lower_left_corner + s*vertical + t*horizontal - origin); 
	}
	
	Vec3<float> origin;
	Vec3<float> lower_left_corner;
	Vec3<float> horizontal;
	Vec3<float> vertical;
	Vec3<float> u, v, w;
	float lens_radius;
};

#endif