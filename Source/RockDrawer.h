#pragma once

#include <Drawer.h>
#include <cmath>
#include <ctime>

class RockDrawer : public Drawer {
public:
	GLuint rockTextureID;
	RockDrawer();
	~RockDrawer();
	void draw(Shader* shader);
	void generateRock();
};