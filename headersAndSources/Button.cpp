#pragma once

#include "Button.hpp"

int Button::width = 150;
int Button::height = 50;

Button::Button() {}
Button::Button(int offsetX, int offsetY) { 
	choosen = false;
	imageIndex = 0;

	hitbox.setX(offsetX);
	hitbox.setY(offsetY);
	hitbox.setWidth(width);
	hitbox.setHeight(height);
}
Hitbox Button::getHitbox() const { return hitbox; }
void Button::setChoosen(bool value) { choosen = value; }
void Button::setImageIndex(int value) { imageIndex = value; }
bool Button::isChoosen() const { return choosen; }
void Button::setImages(const char* imageName1, const char* imageName2) {
	image1.setTexture(imageName1);
	image2.setTexture(imageName2);
}
void Button::draw(const SDL::Manager& manager) const {
	if (imageIndex == 0)
		image1.draw(manager, hitbox);

	if (imageIndex == 1)
		image2.draw(manager, hitbox);
}
	