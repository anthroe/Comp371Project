#pragma once

#include <Drawer.h>

using namespace glm;
class GridDrawer : public Drawer{
	public:
		LineModel* lineModel;
		GridDrawer();
		void drawGrid(Shader* shader);
		void draw(Shader* shader, mat4 worldRotationMatrix);
};