#pragma once

#include "Menu.hpp"

Menu::Menu() { 
	visible = true;
	addButton("pngs\\menu\\play1.png", "pngs\\menu\\play2.png", 500, 375);
	addButton("pngs\\menu\\quit1.png", "pngs\\menu\\quit2.png", 500, 450);

	texts.add(SDL::Image("pngs\\menu\\title.png"));
	texts.add(SDL::Image("pngs\\menu\\credits.png"));
}
bool Menu::isVisible() const { return visible; }
void Menu::addButton(const char* fileName1, const char* fileName2, int offsetX, int offsetY) {
	Button* button = new Button(offsetX, offsetY);
	button->setImages(fileName1, fileName2);
	buttons.insert(button);
}
void Menu::update(int x, int y, bool choose, bool* running) {
	int size = buttons.getSize();
	for (int i = 0; i < size; ++i) {
		if (buttons[i]->getHitbox().containsCoordinate(x, y)) {
			buttons[i]->setImageIndex(1);
			if (choose)
				buttons[i]->setChoosen(true);
				
		}
		else buttons[i]->setImageIndex(0);
	}

	if (buttons[0]->isChoosen())
		visible = false;

	if (buttons[1]->isChoosen())
		*running = false;
}
void Menu::draw(const SDL::Manager& manager) const {
	int size = buttons.getSize();
	for (int i = 0; i < size; ++i)
		buttons[i]->draw(manager);

	texts[0].draw(manager, Hitbox(425, 200, 300, 150));
	texts[1].draw(manager, Hitbox(600, 120, 150, 75));
}
	