#pragma once

#include "Pit.hpp"

int Pit::width = Dirt().getWidth();
int Pit::height = Dirt().getHeight();
SDL::Image Pit::image = SDL::Image();

Pit::Pit() { deadly = true; }
Pit::Pit(int x, int y) { hitbox.resize(x, y, width, height); deadly = true; }
int Pit::getWidth() const { return width; }
void Pit::update() {}
bool Pit::spawnsGoomba() const { return false; }
bool Pit::spawnsMushroom() const { return false; }
void Pit::set(int x, int y) { hitbox.resize(x, y, width, height); }
void Pit::setImage(const char* fileName) { image.setTexture(fileName); }
void Pit::draw(const SDL::Manager& manager) const {}
void Pit::getsHit(bool canBeDestroyed) {}
	