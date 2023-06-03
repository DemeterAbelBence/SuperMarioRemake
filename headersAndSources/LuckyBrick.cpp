#pragma once

#include "LuckyBrick.hpp"

int LuckyBrick::width = 50;
int LuckyBrick::height = 50;

LuckyBrick::LuckyBrick() { used = false; }
LuckyBrick::LuckyBrick(int x, int y) {
	hitbox.resize(x, y, width, height);
	used = false;
	image.setTexture("pngs\\obstacle_pngs\\LuckyBrick.png");
}
void LuckyBrick::set(int x, int y) { hitbox.resize(x, y, width, height); }
void LuckyBrick::update() {}
bool LuckyBrick::spawnsGoomba() const { return false; }
bool LuckyBrick::spawnsMushroom() const { return activated; }
int LuckyBrick::getWidth() const { return width; }
void LuckyBrick::setImage(const char* fileName) { image.setTexture(fileName); }
void LuckyBrick::draw(const SDL::Manager& manager) const { image.draw(manager, hitbox); }
void LuckyBrick::getsHit(bool canBeDestroyed) {
	if (!used) {
		activated = true;
		used = true;
		image.resetTexture("pngs\\obstacle_pngs\\usedLuckyBrick.png");
	}
}
	