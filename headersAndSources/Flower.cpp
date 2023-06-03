#pragma once

#include "Flower.hpp"

int Flower::width = 50;
int Flower::height = 50;
Array<SDL::Image> Flower::images = Array<SDL::Image>();

Flower::Flower() {}
Flower::Flower(int x, int y) {
	state.falling = true;
	state.jumping = false;
	state.movingLeft = false;
	state.movingRight = false;
	state.floating = false;
	state.standing = false;
	state.facingRight = false;
	state.facingLeft = false;
	state.hit = false;
	state.dead = false;

	jumpHeight = 0;
	moveSpeed = 2;
	jumpSpeed = 6;
	fallSpeed = 7;
	imageIndex = 0;

	hitbox.resize(x, y, width, height);
}
int Flower::getHeight() const { return height; }
void Flower::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void Flower::resetImages() {}
void Flower::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void Flower::update() {
	movementTimer.tick();
	if (movementTimer.triggerAction()) {
		if (imageIndex == 0) {
			imageIndex = 1;
		}
		else {
			imageIndex = 0;
		}
	}

	if (state.falling)
		fall(fallSpeed);

	if (state.hit)
		state.dead = true;
}
void Flower::collidesWithObstacle(Obstacle& obstacle) {
	Hitbox obstacleHitbox = obstacle.getHitbox();
	Hitbox h = hitbox;

	if (hitbox.upCollisionWith(obstacleHitbox)) {
		state.falling = false;
		jumpHeight = obstacleHitbox.getY() - jumpLimit;
		state.floating = false;
	}

	h.moveX(5);
	if (h.leftCollisionWith(obstacleHitbox)) {
		state.movingRight = false;
		state.movingLeft = true;
	}

	h.moveX(-10);
	if (h.rightCollisionWith(obstacleHitbox)) {
		state.movingRight = true;
		state.movingLeft = false;
	}

	if (hitbox.downCollisionWith(obstacleHitbox)) {
		state.jumping = false;
		state.falling = true;
	}
}
void Flower::collidesWithEnemy(Entity& enemy) {
	Hitbox enemyHitbox = enemy.getHitbox();

	if (hitbox.leftCollisionWith(enemyHitbox)) {
		enemy.setMovingRight(true);
		enemy.setMovingLeft(false);
	}

	if (hitbox.rightCollisionWith(enemyHitbox)) {
		enemy.setMovingRight(false);
		enemy.setMovingLeft(true);
	}
}
void Flower::collidesWithPlayer(Entity& player) {
	Hitbox playerHitbox = player.getHitbox();

	if (hitbox.collidesWith(playerHitbox)) {
		state.dead = true;
		if (!player.isBig()) {
			player.changeHitboxHeight(40);
			player.setBig(true);
			int newJumpLimit = player.getJumpLimit() + 50;
			player.setJumpLimit(newJumpLimit);
		}				
		player.setAblaze(true);
		player.resetImages();
	}
}
	