#pragma once

#include <glm/glm.hpp>
#include <cstring>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>


using namespace std;
using namespace glm;
class OBJloader {
	public:
		static bool loadOBJ(const char* path, vector<vec3>& out_vertices, vector<vec3>& out_normals, vector<vec2>& out_uvs);
};