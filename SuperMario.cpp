#pragma once

#include "headersAndSources/SDLhandling.hpp"
#include "headersAndSources/Game.hpp"

//#include <vld.h>

int main() {
	SDL::Manager manager("SuperMario", 1200, 700);
	SDL::Image().setRenderer(manager);
	Game game(manager);

	const int FPS = 60;
	const float frameTime = 1000 / FPS;
	float previousTime = 0;
	float currentTime = 0;
	float deltaTime = 0;

	try {
		while (game.isRunning()) {
			previousTime = currentTime;

			game.update(manager);
			game.draw(manager);

			currentTime = manager.getTime();
			deltaTime = (currentTime - previousTime);
			if (frameTime - deltaTime > 0)
				manager.delay(frameTime - deltaTime);
		}
	}
	catch(const char* exception) {
		std::cout << std::endl << exception << std::endl << std::endl;
	}

	return 0;
}