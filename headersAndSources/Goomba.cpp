#pragma once

#include "Goomba.hpp"

int Goomba::width = 60;
int Goomba::height = 60;
Array<SDL::Image> Goomba::images = Array<SDL::Image>();

Goomba::Goomba() {}
Goomba::Goomba(int x, int y) : deathTimer(20) {
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
int Goomba::getHeight() const { return height; }
void Goomba::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void Goomba::resetImages() {}
void Goomba::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void Goomba::update() {
	movementTimer.tick();

	if (state.movingLeft) {
		if(!state.hit)
			moveX(-moveSpeed);

		if (movementTimer.triggerAction()) {
			if (imageIndex == 0) {
				imageIndex = 1;
			}
			else {
				imageIndex = 0;
			}
		}
	}

	if (state.movingRight) {
		if (!state.hit)
			moveX(moveSpeed);

		if (movementTimer.triggerAction()) {
			if (imageIndex == 0) {
				imageIndex = 1;
			}
			else {
				imageIndex = 0;
			}
		}
	}

	if (state.falling)
		fall(fallSpeed);

	if (state.hit) {
		deathTimer.tick();
		imageIndex = 2;
		if (deathTimer.triggerAction()) {
			state.hit = false;
			state.dead = true;
		}
	}
}
void Goomba::collidesWithObstacle(Obstacle& obstacle) {
	Hitbox obstacleHitbox = obstacle.getHitbox();
	Hitbox h = hitbox;

	if (obstacle.isDeadly()) {
		if (hitbox.collidesWith(obstacleHitbox))
			state.dead = true;
	}

	if (hitbox.upCollisionWith(obstacleHitbox)) {
		state.falling = false;
		jumpHeight = obstacleHitbox.getY() - jumpLimit;
		state.floating = false;

		if (!state.movingLeft && !state.movingLeft) {
			state.movingLeft = false;
			state.movingRight = true;
		}
		hitbox.adjustTo(obstacleHitbox);
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
void Goomba::collidesWithEnemy(Entity& enemy) {
	Hitbox enemyHitbox = enemy.getHitbox();
		
	if (hitbox.leftCollisionWith(enemyHitbox) && !enemy.isHit()) {
		state.movingRight = false;
		state.movingLeft = true;
		enemy.setMovingRight(true);
		enemy.setMovingLeft(false);
	}

	if (hitbox.rightCollisionWith(enemyHitbox) && !enemy.isHit()) {
		state.movingRight = true;
		state.movingLeft = false;

		enemy.setMovingRight(false);
		enemy.setMovingLeft(true);
	}
}
void Goomba::collidesWithPlayer(Entity& player) {
	Hitbox playerHitbox = player.getHitbox();

	if (hitbox.leftCollisionWith(playerHitbox)) {
		if(!state.hit)
			player.setHit(true);
		state.movingLeft = true;
		state.movingRight = false;
		return;
	}
	if (hitbox.rightCollisionWith(playerHitbox)) {
		if (!state.hit)
			player.setHit(true);
		state.movingLeft = false;
		state.movingRight = true;
		return;
	}
	if (hitbox.upCollisionWith(playerHitbox)) {
		player.setHit(true);
		return;
	}
	if (hitbox.downCollisionWith(playerHitbox)) {
		if (!state.hit) {
			resetMovementTimer();
			player.setJumping(true);
			player.setFalling(false);

			if(player.isBig())
				player.setJumpHeight(hitbox.getY() - 200);
			else 
				player.setJumpHeight(hitbox.getY() - 150);
		}

		state.hit = true;
		state.movingLeft = false;
		state.movingRight = false;
	}
}
	