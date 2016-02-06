#ifndef DIELETRIC_
#define DIELETRIC_

#include "Material.hpp"

class Dieletric : public Material
{
public:
	Dieletric(float ri):ref_idx(ri){}

	virtual bool scatter(Ray<float> & r_in, hit_record & rec, Vec3<float> & attenuation, Ray<float> & scattered) const{
		Vec3<float> outward_normal;
		Vec3<float> reflected = Vec3<float>::reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = Vec3<float>(1.0,1.0,1.0);
		Vec3<float> refracted;
		float reflect_prob;
		float cosine;

		if (Vec3<float>::dot(r_in.direction(), rec.normal) > 0){
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * Vec3<float>::dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		else{
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -Vec3<float>::dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}

		/*if (Vec3<float>::refract(r_in.direction(), outward_normal, ni_over_nt, refracted)){
			scattered = Ray<float>(rec.p, refracted);
		}
		else{
			scattered = Ray<float>(rec.p, reflected);
			return false;
		}*/
		if (Vec3<float>::refract(r_in.direction(), outward_normal, ni_over_nt, refracted)){
			reflect_prob = Schlick(cosine, ref_idx);
		}
		else{
			scattered = Ray<float>(rec.p, reflected);
			reflect_prob = 1.0;
		}

		if (Rand() < reflect_prob){
			scattered = Ray<float>(rec.p, reflected);
		}
		else{
			scattered = Ray<float>(rec.p, refracted);
		}

		return true;
	}

	float ref_idx;
};

#endif