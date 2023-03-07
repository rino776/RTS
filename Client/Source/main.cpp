#include <memory>
#include <thread>
#include <RenderingEngine.h>
#include <Entity.h>
#include <Transform.h>
#include <Sprite.h>

/*
* Explanation of Namespaces:
* rendering - anything specific to the rendering
* core - anything that needs to be shared accross namespaces
* 
* Possible future namespaces:
* client
* exporter? (Importer as well? or combine into one? or leave as part of client...?)
* 
* server?
* physics
* Maths?
* 
*/
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
	ent->addComponent(new Sprite());	

	while (!renderingEngine->shouldClose()) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("waiting...\n");
		ent->update();
	}

	printf("All Done!\n");
	return 0;
}