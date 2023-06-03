#pragma once

#include "Pipe.hpp"

int Pipe::width = 80;
int Pipe::height = 150;
SDL::Image Pipe::image = SDL::Image();

Pipe::Pipe() {}
Pipe::Pipe(int x, int y) { hitbox.resize(x, y, width, height); }
void Pipe::set(int x, int y) { hitbox.resize(x, y, width, height); }
void Pipe::update() {}
bool Pipe::spawnsGoomba() const { return false; }
bool Pipe::spawnsMushroom() const { return false; }
int Pipe::getWidth() const { return width; }
void Pipe::setImage(const char* fileName) { image.setTexture(fileName); }
void Pipe::draw(const SDL::Manager& manager) const { image.draw(manager, hitbox); }
void Pipe::getsHit(bool canBeDestroyed) {}
	