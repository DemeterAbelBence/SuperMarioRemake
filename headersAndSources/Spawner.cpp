#pragma once

#include "Spawner.hpp"

int Spawner::width = 80;
int Spawner::height = 150;
SDL::Image Spawner::image = SDL::Image();

Spawner::Spawner() {}
Spawner::Spawner(int x, int y) : spawnTimer(spawnPeriod) { 
	hitbox.resize(x, y, width, height);
	activated = false;
}
void Spawner::set(int x, int y) { hitbox.resize(x, y, width, height); }
void Spawner::update() { 
	spawnTimer.tick(); 
	if (spawnTimer.triggerAction())
		activated = true;
}
bool Spawner::spawnsGoomba() const { return activated; }
bool Spawner::spawnsMushroom() const { return false; }
int Spawner::getWidth() const { return width; }
void Spawner::setImage(const char* fileName) { image.setTexture(fileName); }
void Spawner::draw(const SDL::Manager& manager) const { image.draw(manager, hitbox); }
void Spawner::getsHit(bool canBeDestroyed) {}
	