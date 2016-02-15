#include <iostream>
#include <stdio.h>

#include "Image.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitablelist.hpp"
#include "Sphere.hpp"
#include "SimpleRand.hpp"
#include "Lambertian.hpp"

#include <random>

int main(int argc, char ** argv){

	int width = 200, height = 100;
	Image<float> im(width, height);

	//Vec3<float>a(50.0, 0, 0); a.normalize();
	//cout << "a =" << a.x() << " " << a.y() << " " << a.z() << endl;
	//myteste

	srand(1000);
	im.saveImage("teste.ppm");
	

	system("pause");
	

	return 0;
}