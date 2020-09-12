#pragma once

#include "MichaelMath.h"
#include <vector>

class Mesh
{
public:
	Mesh() = delete;
	Mesh(const char* fileName);
	~Mesh();

	int NumberOfVerts() { return (int)verts.size(); }
	int NumberOfFaces() { return (int)faces.size(); }

	std::vector<int> FaceAt(int index) { return faces[index]; }
	Vec3f VertAt(int index) { return verts[index]; }

private:
	std::vector<Vec3f> verts;
	std::vector<std::vector<int>> faces;
};

