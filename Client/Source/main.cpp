#include <memory>
#include <thread>
#include <RenderingEngine.h>
#include <Entity.h>
#include <Transform.h>
#include <Sprite.h>
#include <Mesh.h>

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
	//start the rendering thread
	std::thread renderingThread = renderingEngine->start();

	
	std::vector<Entity*> entities;

	Entity* ent = new Entity();
	ent->addComponent(new Transform());
	//ent->addComponent(new Sprite());	
	ent->addComponent(new Mesh());
	entities.push_back(ent);

	Entity* sprite = new Entity();
	sprite->addComponent(new Transform());
	sprite->addComponent(new Sprite());
	//entities.push_back(sprite);

	renderingEngine->setDirtyEntities(entities);
	entities.clear();

	while (!renderingEngine->shouldClose()) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("waiting...\n");
		ent->update();
	}

	//join the threads back to the main thread
	renderingThread.join();
	printf("All Done!\n");
	return 0;
}