#include <memory>
#include <thread>

#include <RenderingEngine.h>
#include <ObjLoader.h>
#include <Entity.h>
#include <Transform.h>
#include <Sprite.h>
#include <CameraController.h>
#include <Console.h>

/*
* TODO List:
* - improve camera controlls (mouse)
* - basic game server (how the hell to do that? need more research lol)
* - finish loading meshes from .obj files (deal with non-triangulated meshes)
* - generate normals for meshes that don't have them
* - add support for other mesh files?
* - different types of lighting?
*	- change lighting to view space
* - load sprites from file
* - textures
* - basic ui
*	- buttons
*	- debug console?
* - start and stop rendering via cmd line
*/

/*
* game server thoughts/TODO list:
* - set up basic commands (so, doesn't render right away... 
	and allows you to connect via console before beginning rendering)
* - set up basic socket connection
* - figure out what data needs to be sent
* - serialize data
* - game lobby?/ connection lobby?
* - 
*/


/*
 * note: if adding new projects
 * right click client -> add -> references
 * 
 */

/*
* Explanation of Namespaces:
* rendering - anything specific to the rendering
* core - anything that needs to be shared accross namespaces
* loader - anything that loads data from files.
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
using namespace loader;
using namespace client;

//TODO: move these into thier own class - they shouldn't be public


void updateEntities(RenderingEngine* renderingEngine, std::vector<Entity*> entities, 
	std::vector<Entity*> dirtyEnts, CameraController* cam) {
	for (Entity* e : entities) {
		e->update();

		if (e->isDirty()) {
			dirtyEnts.push_back(e);
		}
	}

	//special for just the cameraController
	if (cam->isDirty()) {
		Transform* cameraTransform = (Transform*)(cam->getComponent(eTransform));
		renderingEngine->setCameraTransform(cameraTransform);
	}

	if (!dirtyEnts.empty()) {
		renderingEngine->setDirtyEntities(dirtyEnts);
		dirtyEnts.clear();
	}
}

int main(int args, char** argv) 
{
	//should we render a window? or just the console?
	bool bHeadless = false;

	//allow custom settings
	if (args > 1) {

		for (int i = 1; i < args; i++) {
			const char* param = argv[i];
			if (strcmp(param, "--server") == 0) {
				printf("running as server\n");
				bHeadless = true;
			}
			else {
				printf("using defaults\n");
			}
		}
	}

	std::vector<Entity*> entities;
	std::vector<Entity*> dirtyEnts;

	std::shared_ptr<InputManager> inputManager = std::make_shared<InputManager>(InputManager());
	std::unique_ptr<RenderingEngine> renderingEngine = std::make_unique<RenderingEngine>(RenderingEngine(inputManager));
	std::unique_ptr<Console> console = std::make_unique<Console>(Console());

	//start the rendering thread
	std::thread renderingThread;
	std::thread consoleThread = console->start();
	if(!bHeadless)
		renderingThread = renderingEngine->start();
	

	Entity* ent = new Entity();
	ent->addComponent(new Transform(glm::vec3(0.0, -0.7, -4.0)));
	//ent->addComponent(new Sprite());	
	ent->addComponent(ObjLoader::loadFromFile("Models/teapot.obj"));
	entities.push_back(ent);

	Entity* sprite = new Entity();
	sprite->addComponent(new Transform());
	sprite->addComponent(new Sprite());
	//entities.push_back(sprite);

	CameraController* cam = new CameraController();
	entities.push_back(cam);
	if(!bHeadless)
		renderingEngine->setDirtyEntities(entities);

	for (Entity* e : entities) {
		e->setInputManager(inputManager);
	}
	
	while (!renderingEngine->shouldClose() && !console->shouldClose()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		if (!bHeadless)
			updateEntities(renderingEngine.get(), entities, dirtyEnts, cam);
	}
	
	renderingEngine->setShouldClose(true);
	console->setShouldClose(true);

	//join the threads back to the main thread
	if(!bHeadless)
		renderingThread.join();
	
	consoleThread.join();
	printf("All Done!\n");
	return 0;
}
