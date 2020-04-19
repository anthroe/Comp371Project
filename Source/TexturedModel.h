
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

class TexturedModel : public Model {
public:
	TexturedModel();
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture, GLenum drawingPrimitive);
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color, GLuint texture);
	TexturedModel(vec3 position, vec3 rotation, vec3 scaling, vec3 color);
	TexturedModel(vec3 position, vec3 scaling, vec3 color);
	~TexturedModel();
	void setVAO(GLuint VAO, int verticesCount);
	void draw(Shader* shader);
	//protected:
	  //  virtual bool ParseLine(const std::vector<ci_string> &token);
	private:
		unsigned int mVAO;
		unsigned int numOfVertices;
};