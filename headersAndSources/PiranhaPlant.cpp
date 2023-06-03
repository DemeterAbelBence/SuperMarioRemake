#pragma once

#include "PiranhaPlant.hpp"

int PiranhaPlant::width = 60;
int PiranhaPlant::height = 60;
Array<SDL::Image> PiranhaPlant::images = Array<SDL::Image>();

PiranhaPlant::PiranhaPlant() {}
PiranhaPlant::PiranhaPlant(int x, int y, int h) {
	state.falling = false;
	state.jumping = true;
	state.movingLeft = false;
	state.movingRight = false;
	state.floating = false;
	state.standing = false;
	state.facingRight = false;
	state.facingLeft = false;
	state.hit = false;
	state.dead = false;

	jumpHeight = 0;
	moveSpeed = 1;
	jumpSpeed = 6;
	fallSpeed = 7;
	imageIndex = 0;

	for (int i = 0; i < h; ++i)
		biteTimer.tick();

	biteTimer.set(20);
	movementTimer.set(150);

	hitbox.resize(x, y, width, height);
}
int PiranhaPlant::getHeight() const { return height; }
void PiranhaPlant::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void PiranhaPlant::resetImages() {}
void PiranhaPlant::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void PiranhaPlant::update() {
	biteTimer.tick();
	if (biteTimer.triggerAction()) {
		if (imageIndex == 0) {
			imageIndex = 1;
		}
		else {
			imageIndex = 0;
		}
	}
	if (state.jumping)
		moveY(moveSpeed);
			
	if (state.falling)
		moveY(-moveSpeed);

	movementTimer.tick();
	if (movementTimer.triggerAction()) {
		if (state.jumping) {
			state.jumping = false;
			state.falling = true;
			return;
		}
		if (state.falling) {
			state.jumping = true;
			state.falling = false;
			return;
		}
	}
}
void PiranhaPlant::collidesWithObstacle(Obstacle& obstacle) {}
void PiranhaPlant::collidesWithEnemy(Entity& enemy) {}
void PiranhaPlant::collidesWithPlayer(Entity& player) {
	Hitbox playerHitbox = player.getHitbox();

	if (hitbox.collidesWith(playerHitbox))
		player.setHit(true);
}
	