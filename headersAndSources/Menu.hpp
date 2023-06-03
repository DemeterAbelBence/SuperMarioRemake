#pragma once

#include "Button.hpp"
#include "Array.hpp"
#include "Collection.hpp"

class Menu {

private:
	bool visible;
	Collection<Button> buttons;
	Array<SDL::Image> texts;

public:
	Menu();
	bool isVisible() const;
	void addButton(const char* fileName1, const char* fileName2, int offsetX, int offsetY);
	void update(int x, int y, bool choose, bool* running);
	void draw(const SDL::Manager& manager) const;
};

