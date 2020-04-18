#pragma once
//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <vector>

#include <Model.h>

#include <string>
#include "OBJloader.h"
#include "OBJloaderV2.h"
class TexturedModel : public Model {
public:
	TexturedModel();
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, string name);
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture);
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color);
	TexturedModel(vec3 position, vec3 scaling, vec3 color);
	~TexturedModel();
	void draw(Shader* shader);
	void init();
	void init(string name);
	//protected:
	  //  virtual bool ParseLine(const std::vector<ci_string> &token);


	GLuint setupModelVBO(std::string path, int& vertexCount);
	void setupModelEBO(std::string path);

	private:
		unsigned int mVAO;
		unsigned int mEBO;
		unsigned int numOfVertices;
};