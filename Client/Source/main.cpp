#include <memory>
#include <thread>
#include <RenderingEngine.h>


using namespace rendering;

int main() 
{
	std::unique_ptr<RenderingEngine> renderingEngine = std::make_unique<RenderingEngine>(RenderingEngine());

	//renderingEngine->init();

	std::thread renderingThread = renderingEngine->start();

	printf("Hello From Main thread \n");
	
	renderingThread.detach();

	printf("waiting for rendering thread \n");

	while (!renderingEngine->shouldClose()) {
		std::this_thread::sleep_for(std::chrono::seconds(1));
		printf("waiting...\n");
	}

	printf("All Done!\n");
	return 0;
}