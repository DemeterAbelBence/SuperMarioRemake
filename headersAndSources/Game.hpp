#pragma once

#include "Map.hpp"
#include "Menu.hpp"
#include "Mouse.hpp"

class Game{
	
private:
	bool running = true;
	static const int mapSize = 10;

	Map<mapSize>* map;

	SDL::Event userEvent;
	Mouse mouse;
	Menu menu;
	Player player;

private:
	void handleEvents();

public:
	Game();
	Game(const SDL::Manager& manager);
	void update(const SDL::Manager& manager);
	bool isRunning() const;
	void draw(const SDL::Manager& manager) const;

	~Game();
};
