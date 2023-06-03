#pragma once

#include "Brick.hpp"

int Brick::width = 50;
int Brick::height = 50;
SDL::Image Brick::image = SDL::Image();

Brick::Brick() {}
Brick::Brick(int x, int y) { hitbox.resize(x, y, width, height); }
void Brick::set(int x, int y) { hitbox.resize(x, y, width, height); }
void Brick::update() {}
bool Brick::spawnsGoomba() const { return false; }
bool Brick::spawnsMushroom() const { return false; }
int Brick::getWidth() const { return width; }
void Brick::setImage(const char* fileName) { image.setTexture(fileName); }
void Brick::draw(const SDL::Manager& manager) const { image.draw(manager, hitbox); }
void Brick::getsHit(bool canBeDestroyed) { if(canBeDestroyed)destroyed = true; }
	