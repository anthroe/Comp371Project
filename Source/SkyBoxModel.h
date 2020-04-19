#pragma once
#include <Model.h>

class SkyBoxModel : public Model {
	public:
		SkyBoxModel(GLuint texture);
		~SkyBoxModel();
		void draw(Shader* shader);
		void init();
    private:

        struct Vertex
        {
            vec3 position;
        };

        unsigned int mVAO;
        unsigned int mVBO;
        unsigned int numOfVertices;
};