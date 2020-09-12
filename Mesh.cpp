#include "Mesh.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

Mesh::Mesh(const char* fileName)
{
	std::ifstream in;
	in.open(fileName, std::ifstream::in);
	if (in.fail())
	{
		std::cerr << "File " << fileName << " not found!" << std::endl;
	}

	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		std::istringstream iss(line.c_str());
		char trash;
		if (!line.compare(0, 2, "v ")) 
		{
			iss >> trash;
			Vec3f v;
			for (int i = 0; i < 3; ++i) iss >> v.raw[i];
			verts.push_back(v);
		}
		else if (!line.compare(0, 2, "f ")) 
		{
			std::vector<int> f;
			int itrash, idx;
			iss >> trash;
			while (iss >> idx >> trash >> itrash >> trash >> itrash)
			{
				idx--;
				f.push_back(idx);
			}
			faces.push_back(f);
		}
	}

	std::cerr << "Number of Vertices: " << verts.size() << std::endl << "Number of Faces: " << faces.size() << std::endl;
}

Mesh::~Mesh()
{
}