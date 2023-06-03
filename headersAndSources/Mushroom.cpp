#pragma once

#include "Mushroom.hpp"

int Mushroom::width = 50;
int Mushroom::height = 50;
Array<SDL::Image> Mushroom::images = Array<SDL::Image>();

Mushroom::Mushroom() {}
Mushroom::Mushroom(int x, int y) {
	state.falling = true;
	state.jumping = false;
	state.movingLeft = true;
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
int Mushroom::getHeight() const { return height; }
void Mushroom::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void Mushroom::resetImages() {}
void Mushroom::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void Mushroom::update() {
	movementTimer.tick();
	if (movementTimer.triggerAction()) {
		if (imageIndex == 0) {
			imageIndex = 1;
		}
		else {
			imageIndex = 0;
		}
	}

	if (state.movingLeft)
		moveX(-moveSpeed);

	if (state.movingRight)
		moveX(moveSpeed);

	if (state.falling)
		fall(fallSpeed);

	if (state.hit)
		state.dead = true;
}
void Mushroom::collidesWithObstacle(Obstacle& obstacle) {
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
void Mushroom::collidesWithEnemy(Entity& enemy) {
	Hitbox enemyHitbox = enemy.getHitbox();

	if (hitbox.leftCollisionWith(enemyHitbox)) {
		state.movingRight = false;
		state.movingLeft = true;
		enemy.setMovingRight(true);
		enemy.setMovingLeft(false);
	}

	if (hitbox.rightCollisionWith(enemyHitbox)) {
		state.movingRight = true;
		state.movingLeft = false;
		enemy.setMovingRight(false);
		enemy.setMovingLeft(true);
	}
}
void Mushroom::collidesWithPlayer(Entity& player) {
	Hitbox playerHitbox = player.getHitbox();

	if(hitbox.collidesWith(playerHitbox)){
		state.dead = true;
		if (!player.isBig()) {
			player.changeHitboxHeight(40);
			player.setBig(true);
			int newJumpLimit = player.getJumpLimit() + 50;
			player.setJumpLimit(newJumpLimit);
		}
	}
}
	