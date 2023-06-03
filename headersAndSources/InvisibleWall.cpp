#pragma once

#include "InvisibleWall.hpp"

int InvisibleWall::width = 10;
int InvisibleWall::height = 800;

InvisibleWall::InvisibleWall() {}
InvisibleWall::InvisibleWall(int x, int y) { hitbox.resize(x, y, width, height); }
void InvisibleWall::set(int x, int y) { hitbox.resize(x, y, width, height); }
void InvisibleWall::update() {}
bool InvisibleWall::spawnsGoomba() const { return false; }
bool InvisibleWall::spawnsMushroom() const { return false; }
int InvisibleWall::getWidth() const { return width; }
void InvisibleWall::setImage(const char* fileName) {}
void InvisibleWall::draw(const SDL::Manager& manager) const {}
void InvisibleWall::getsHit(bool canBeDestroyed) {}
	