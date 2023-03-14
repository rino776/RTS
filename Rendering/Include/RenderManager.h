#pragma once

namespace rendering{

	class RenderManager
{
public:
	RenderManager();
	virtual ~RenderManager();
	void init();
	void update();
	void render();


};
}
