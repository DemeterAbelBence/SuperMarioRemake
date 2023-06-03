#pragma once

#include "Obstacle.hpp"

Obstacle::Obstacle() { destroyed = false; activated = false; deadly = false; }
Obstacle::Obstacle(int x, int y, int w, int h) {
	activated = false;
	hitbox.resize(x, y, w, h);
}
void Obstacle::setY(int value) { hitbox.setY(value); }
void Obstacle::setActivated(int value) { activated = value; }
void Obstacle::setDeadly(bool value) { deadly = value; }
bool Obstacle::isDestroyed() const { return destroyed; }
bool Obstacle::isActivated() const { return activated; }
bool Obstacle::isDeadly() const { return deadly; }
Hitbox Obstacle::getHitbox() const { return hitbox; }
void Obstacle::moveX(int value) { hitbox.moveX(value); }
void Obstacle::moveY(int value) { hitbox.moveY(value); }
	