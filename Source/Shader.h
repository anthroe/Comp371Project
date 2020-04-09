//
//  shader.h
//  A1_40061204
//
//  Header file for the Shader class. See "shader.cpp" for the implementation.
//
//  Created by Édouard Gagné on 2020-02-22.
//

#ifndef shader_h
#define shader_h

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/glm.hpp>

#include <stdlib.h>

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace glm;
using namespace std;

class Shader {
    public:
        string name;
        GLuint ProgramID;
        Shader(string name, string vertex_shader_path, string fragment_shader_path);
        void use();
        void setMat4(const string &name, const mat4 &mat);
        void setVec3(const string &name, const vec3 &value);
        void setVec3(const string& name, float x, float y, float z);
        void setInt(const string &name, int value);
        void setFloat(const string &name, float value);
        void setBool(const string &name, bool value);
    private:
        void checkCompileErrors(GLuint shader, string type);
        string getShaderCode(string shader_path);
};
#endif
