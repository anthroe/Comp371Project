<<<<<<< Updated upstream
<<<<<<< Updated upstream
#pragma once
//
// COMP 371 Assignment Framework
//
// Created by Nicolas Bergeron on 8/7/14.
// Updated by Gary Chang on 14/1/15
//
// Copyright (c) 2014-2019 Concordia University. All rights reserved.
//

#pragma once
//#include <GL/glew.h>    // Include GLEW - OpenGL Extension Wrangler
//
//#include <GLFW/glfw3.h> // cross-platform interface for creating a graphical context,
//						// initializing OpenGL and binding inputs
//
#include <glm/glm.hpp>  // GLM is an optimized math library with syntax to similar to OpenGL Shading Language
#include <vector>

#include <string>
#include "OBJloader.h"
#include "OBJloaderV2.h"
class TexturedModel {
public:
	GLuint setupModelVBO(std::string path, int& vertexCount)
	{
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> UVs;

		//read the vertex data from the model's OBJ file
		loadOBJ(path.c_str(), vertices, normals, UVs);

		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO); //Becomes active VAO
		// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).

		//Vertex VBO setup
		GLuint vertices_VBO;
		glGenBuffers(1, &vertices_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, vertices_VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		//Normals VBO setup
		GLuint normals_VBO;
		glGenBuffers(1, &normals_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, normals_VBO);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(1);

		//UVs VBO setup
		GLuint uvs_VBO;
		glGenBuffers(1, &uvs_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, uvs_VBO);
		glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
		// Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs, as we are using multiple VAOs)
		vertexCount = vertices.size();
		return VAO;
	}
	


=======
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
	void draw(Shader* shader, GLuint drawingPrimitive);
	void init();
	//protected:
	  //  virtual bool ParseLine(const std::vector<ci_string> &token);


	GLuint setupModelVBO(std::string path, int& vertexCount);
	void setupModelEBO(std::string path);

	private:
		unsigned int mVAO;
		unsigned int mEBO;
		unsigned int numOfVertices;
>>>>>>> Stashed changes
=======
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
	void draw(Shader* shader, glm::mat4 WorldMatrix, GLuint drawingPrimitive);
	void draw(Shader* shader, GLuint drawingPrimitive);
	void init();
	//protected:
	  //  virtual bool ParseLine(const std::vector<ci_string> &token);


	GLuint setupModelVBO(std::string path, int& vertexCount);
	void setupModelEBO(std::string path);

	private:
		unsigned int mVAO;
		unsigned int mEBO;
		unsigned int numOfVertices;
>>>>>>> Stashed changes
};