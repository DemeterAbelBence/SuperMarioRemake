#pragma once

#include "SDLhandling.hpp"

template<int size>
class Background {

private:
	SDL::Image images[size];

	int width;
	int height;
	int offsetX;
	int offsetY;

public:
	Background();
	void set(const char* fileName, int x, int y, int w, int h);
	void move(int value);
	void draw(const SDL::Manager& manager) const;
};

template<int size>
Background<size>::Background() {}

template<int size>
void Background<size>::set(const char* fileName, int x, int y, int w, int h) {

	for (int i = 0; i < size; ++i) {
		images[i].setTexture(fileName);
	}

	offsetX = x;
	offsetY = y;
	width = w;
	height = h;
}

template<int size>
void Background<size>::move(int value) { offsetX += value; }

template<int size>
void Background<size>::draw(const SDL::Manager& manager) const {
	for (int i = 0; i < size; ++i) {
		manager.drawImage(images[i].getTexture(), offsetX + i * width, offsetY, width, height);
	}
}
