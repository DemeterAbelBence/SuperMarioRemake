#pragma once

#include "SDLhandling.hpp"
#include "Hitbox.hpp"
#include "Array.hpp"

class Button{

private:
	Hitbox hitbox;
	SDL::Image image1;
	SDL::Image image2;

	bool choosen;
	int imageIndex;

	static int width;
	static int height;
	

public:
	Button();
	Button(int offsetX, int offsetY);
	Hitbox getHitbox() const;
	void setChoosen(bool value);
	void setImageIndex(int value);
	bool isChoosen() const;

	void setImages(const char* imageName1, const char* imageName2);
	void draw(const SDL::Manager& manager) const;
};
