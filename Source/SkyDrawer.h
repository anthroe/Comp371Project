#pragma once

#include "Drawer.h"
#include "SkyBoxModel.h"

class SkyDrawer : public Drawer {
	public:
		SkyBoxModel* skyBox;
		SkyDrawer();
		~SkyDrawer();
		void draw(Shader* shader);
		void createModels();
};
