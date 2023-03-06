#include <memory>
#include <thread>
#include <RenderingEngine.h>
#include <Entity.h>
#include <Transform.h>


using namespace rendering;
using namespace core;

int main() 
{
	std::unique_ptr<RenderingEngine> renderingEngine = std::make_unique<RenderingEngine>(RenderingEngine());

	//renderingEngine->init();

	std::thread renderingThread = renderingEngine->start();

	printf("Hello From Main thread \n");
	
	renderingThread.detach();

	printf("waiting for rendering thread \n");

	Entity* ent = new Entity();
	ent->addComponent(new Transform());

	while (!renderingEngine->shouldClose()) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("waiting...\n");
		ent->update();
	}

	printf("All Done!\n");
	return 0;
}