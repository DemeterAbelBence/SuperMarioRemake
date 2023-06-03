#pragma once

#include "Hitbox.hpp"

Hitbox::Hitbox() {
	x = 0; 
	y = 0;

	width = 0;
	height = 0;
}
Hitbox::Hitbox(int x0, int y0, int w, int h) {
	x = x0;
	y = y0;

	width = w;
	height = h;
}
void Hitbox::setX(int x0) { x = x0; }
void Hitbox::setY(int y0) { y = y0; }
void Hitbox::setWidth(int w) { width = w; }
void Hitbox::setHeight(int h) { height = h; }
void Hitbox::resize(int x0, int y0, int w, int h) {
	x = x0;
	y = y0;
	width = w;
	height = h;
}
int Hitbox::getX() const{ return x; }
int Hitbox::getY() const{ return y; }
int Hitbox::getWidth() const{ return width; }
int Hitbox::getHeight() const{ return height; }
void Hitbox::operator=(const Hitbox& H) {
	x = H.getX();
	y = H.getY();
	width = H.getWidth();
	height = H.getHeight();
}
void Hitbox::extend(int value) {
	width += value;
	height += value;
}
bool Hitbox::leftCollisionWith(const Hitbox& h) const {
	int deltaX = abs(x - h.getX());
	int deltaY = abs(y - h.getY());
	int eps = 10;

	if (x < h.getX() && deltaX < width) {
		if (y <= h.getY() && deltaY < height - eps) 
			return true;

		if (y >= h.getY() && deltaY < h.getHeight() - eps)
			return true;
	}
	return false;
}
bool Hitbox::rightCollisionWith(const Hitbox& h) const {
	int deltaX = abs(x - h.getX());
	int deltaY = abs(y - h.getY());
	int eps = 10;

	if (x > h.getX() && deltaX < h.getWidth()) {
		if (y < h.getY() && deltaY < height - eps)
			return true;

		if (y > h.getY() && deltaY < h.getHeight() - eps)
			return true;
	}
	return false;
}
bool Hitbox::upCollisionWith(const Hitbox& h) const {
	int deltaX = abs(x - h.getX());
	int deltaY = abs(y - h.getY());

	if (y < h.getY() && deltaY < height) {
		if (x <= h.getX() && deltaX < width)
			return true;

		if (x > h.getX() && deltaX < h.getWidth())
			return true;
	}
	return false;
}
bool Hitbox::downCollisionWith(const Hitbox& h) const {
	int deltaX = abs(x - h.getX());
	int deltaY = abs(y - h.getY());

	if (y > h.getY() && deltaY < h.getHeight()) {
		if (x <= h.getX() && deltaX < width)
			return true;

		if (x > h.getX() && deltaX < h.getWidth())
			return true;
	}
	return false;
}
bool Hitbox::collidesWith(const Hitbox& h) const {
	return leftCollisionWith(h) || rightCollisionWith(h) || upCollisionWith(h) || downCollisionWith(h);
}
bool Hitbox::inFrontOf(const Hitbox& h) const {
	bool result = false;
	if (abs(x + width - h.getX()) < 10)
		result = true;

	if (abs(x - h.getX() - h.getWidth()) < 10)
		result = true;

	return result;
}
void Hitbox::adjustTo(const Hitbox& h) {
	while (y  + height - 5 > h.getY())
		--y;
}
bool Hitbox::containsCoordinate(int x0, int y0) const {
	return x0 > x && x0 < x + width && y0 > y && y0 < y + height;
}
void Hitbox::moveX(int value) { x += value; }
void Hitbox::moveY(int value) { y += value; }
	