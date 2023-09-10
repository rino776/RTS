#include "Console.h"

using namespace client;
using namespace rendering;

Console::Console() :
		m_shouldClose(false)
{

}

std::thread Console::start() {
    return std::thread(&Console::init, this);
}

void Console::init() {
    //nothing to init right n
    update();
}

void Console::update() {
	while (!m_shouldClose) {
		printf("Please enter command: \n");
		char str[80];
		scanf_s("%s", &str, (unsigned)_countof(str));

		if (strcmp("exit", str) == 0) {
			m_shouldClose = true;
			printf("Now exiting!\n");
		}
		else {
			printf("Invalid command!\n");
		}
	}
	printf("Exiting console Update!\n");

}
