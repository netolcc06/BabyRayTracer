#ifndef MESH_
#define MESH_

#include <stdlib.h>
#include <vector>

#include <fstream>
//#include <iostream>
#include <sstream>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "Hitable.hpp"
#include "Material.hpp"
#include "Triangle.hpp"

using namespace std;

class Mesh : public Hitable
{
public:
	Mesh() {}
	Mesh(std::string path, Material * m) {
		material = m;

		std::ifstream in_file(path);
		std::string line, op;
		std::stringstream linestream;
		Vec3<float> tmp_position;
		float x, y, z;

		int count = 0;

		while (std::getline(in_file, line))
		{
			linestream << line;
			linestream >> op;

			if (op == "v") {

				//tmp_vert = new _Vertex_();

				linestream >> x >> y >> z;
				//tmp_vert->id = count;
				Vec3<float> tmp_vert(x, y, z);
				//std::cout << x << " " << y << " " << z << std::endl;
				//mesh->AddVertex(tmp_vert);
				vertices.push_back(tmp_vert);
				//count++;

			}
			else if (op == "f") {
				int v0, v1, v2;
				linestream >> v0 >> v1 >> v2;
				//mesh->CreateFace(mesh->getVertex(v0 - 1)->id, mesh->getVertex(v1 - 1)->id, mesh->getVertex(v2 - 1)->id);
				//std::cout << v0 << " " << v1 << " " << v2 << std::endl;
				faces.push_back(Triangle(vertices.at(v0 - 1), vertices.at(v1 - 1), vertices.at(v2 - 1), m));
			}

			linestream.clear();
		}

		//print();
	}

	void print() {
		for (Vec3<float> v : vertices) {
			std::cout << "vertice = " << v.x() << " " << v.y() << " " << v.z() << std::endl;
		}

		for (Triangle t : faces) {
			std::cout << "triangle = " << t.v0_.x() << " " << t.v0_.y() << " " << t.v0_.z() << std::endl;
			std::cout << "triangle = " << t.v1_.x() << " " << t.v1_.y() << " " << t.v1_.z() << std::endl;
			std::cout << "triangle = " << t.v2_.x() << " " << t.v2_.y() << " " << t.v2_.z() << std::endl;
			std::cout << "-------------------------" << std::endl;
		}

		system("pause");
	}

	virtual bool hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const;

	Material * material;

	std::vector<Vec3<float>> vertices;
	std::vector<Triangle> faces;
};



bool Mesh::hit(Ray<float> & r, float t_min, float t_max, hit_record & rec) const {

	Vec3<float> normal(0, 0, 0);

	float thit = 10000000.0f;
	bool hit = false;

	for (Triangle f : faces)
	{
		if (f.hit(r, t_min, t_max, rec)) {
			if (rec.t < thit) {
				thit = rec.t;
				normal = rec.normal;
			}
			hit = true;
		}

	}

	rec.t = thit;
	//if (Vec3<float>::dot(normal, r.direction()) > 0) normal = -normal;	
	rec.normal = normal;
	rec.p = r.point_at_parameter(rec.t);

	return hit;
}

#endif


