#pragma once

#include "Dirt.hpp"

int Dirt::width = 800;
int Dirt::height = 450;
SDL::Image Dirt::image = SDL::Image();

Dirt::Dirt() { deadly = false; }
Dirt::Dirt(int x, int y) { hitbox.resize(x, y, width, height); }
int Dirt::getHeight() const { return height; }
void Dirt::set(int x, int y) { hitbox.resize(x, y, width, height); }
void Dirt::update() {}
bool Dirt::spawnsGoomba() const { return false; }
bool Dirt::spawnsMushroom() const { return false; }
int Dirt::getWidth() const { return width; }
void Dirt::setImage(const char* fileName) { image.setTexture(fileName); }
void Dirt::draw(const SDL::Manager& manager) const { image.draw(manager, hitbox); }
void Dirt::getsHit(bool canBeDestroyed) {}
	