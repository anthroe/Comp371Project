#pragma once

#include <glm/glm.hpp>
#include <cstring>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
using namespace glm;
class OBJloaderV2 {
	public:
		static bool loadOBJ2(const char* path, vector<int>& vertexIndices, vector<vec3>& temp_vertices, vector<vec3>& out_normals, vector<vec2>& out_uvs);
};
