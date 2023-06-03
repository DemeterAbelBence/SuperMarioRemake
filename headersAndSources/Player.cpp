#pragma once

#include "Player.hpp"

int Player::width = 50;
int Player::height = 60;
Array<SDL::Image> Player::images = Array<SDL::Image>();

Player::Player() : vulnerabilityTimer(150) {
	state.falling = true;
	state.jumping = false;
	state.movingLeft = false;
	state.movingRight = false;
	state.jumpingRight = false;
	state.jumpingLeft = false;
	state.floating = false;
	state.standing = true;
	state.facingRight = true;
	state.facingLeft = false;
	state.hit = false;
	state.dead = false;
	state.big = false;
	state.ablaze = false;
	state.shooting = false;

	jumpHeight = 0;
	jumpLimit = 250;
	moveSpeed = 3;
	jumpSpeed = 7;
	fallSpeed = 7;
	imageIndex = 0;
}
void Player::accelerate() { moveSpeed = sprintSpeed; }
void Player::resetSpeed() { moveSpeed = defaultSpeed; }
void Player::setPosition(int x, int y) { hitbox.resize(x, y, width, height); }
void Player::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void Player::resetImages() {
	images.clear();
	if (state.ablaze) {
		addImage("pngs\\fireMario_pngs\\movingRight1.png");
		addImage("pngs\\fireMario_pngs\\movingRight2.png");
		addImage("pngs\\fireMario_pngs\\movingRight3.png");
		addImage("pngs\\fireMario_pngs\\movingLeft1.png");
		addImage("pngs\\fireMario_pngs\\movingLeft2.png");
		addImage("pngs\\fireMario_pngs\\movingLeft3.png");
		addImage("pngs\\fireMario_pngs\\standingLeft.png");
		addImage("pngs\\fireMario_pngs\\standingRight.png");
		addImage("pngs\\fireMario_pngs\\jumpLeft.png");
		addImage("pngs\\fireMario_pngs\\jumpRight.png");
	}
	else {
		addImage("pngs\\mario_pngs\\movingRight1.png");
		addImage("pngs\\mario_pngs\\movingRight2.png");
		addImage("pngs\\mario_pngs\\movingRight3.png");
		addImage("pngs\\mario_pngs\\movingLeft1.png");
		addImage("pngs\\mario_pngs\\movingLeft2.png");
		addImage("pngs\\mario_pngs\\movingLeft3.png");
		addImage("pngs\\mario_pngs\\standingLeft.png");
		addImage("pngs\\mario_pngs\\standingRight.png");
		addImage("pngs\\mario_pngs\\jumpLeft.png");
		addImage("pngs\\mario_pngs\\jumpRight.png");
	}
}
void Player::update() {
	movementTimer.tick();
	vulnerabilityTimer.tick();

	if (state.hit) {
		if (state.ablaze) {
			state.ablaze = false;
			resetImages();
			vulnerabilityTimer.reset();
		}
		else if (vulnerabilityTimer.triggerAction()) {
			if (state.big) {
				state.big = false;
				changeHitboxHeight(-40);
				jumpLimit -= 50;
				vulnerabilityTimer.reset();
			}
			else state.dead = true;
		}
		state.hit = false;
	} 
		
	if (state.facingLeft) {
		if (state.standing) {
			imageIndex = 6;
			return;
		}
		if (state.jumping) {
			if (state.movingLeft)
				state.jumpingLeft = true;
			imageIndex = 8;
			return;
		}
		if (state.movingLeft && !state.falling) {
			if (imageIndex < 3 || imageIndex > 5) {
				imageIndex = 3;
				return;
			}
			if (movementTimer.triggerAction())
				imageIndex++;
		}
		return;
	}
	if (state.facingRight) {
		if (state.standing) {
			imageIndex = 7;
			return;
		}
		if (state.jumping) {
			if (state.movingRight)
				state.jumpingRight = true;
			imageIndex = 9;
			return;
		}
		if (state.movingRight && !state.falling) {
			if (imageIndex > 2) {
				imageIndex = 0;
				return;
			}
				
			if (movementTimer.triggerAction())
				imageIndex++;
		}
		return;
	}
}
void Player::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void Player::collidesWithObstacle(Obstacle& obstacle) {
	Hitbox obstacleHitbox = obstacle.getHitbox();
	Hitbox h = hitbox;

	if (obstacle.isDeadly()) {
		if (hitbox.collidesWith(obstacleHitbox))
			state.dead = true;
	}

	if (hitbox.upCollisionWith(obstacleHitbox)) {
			state.falling = false;
			if(!state.jumpingRight && !state.jumpingLeft)
				jumpHeight = obstacleHitbox.getY() - jumpLimit;
			state.floating = false;

			if (!state.movingLeft && !state.movingRight && !state.jumping)
				state.standing = true;

			hitbox.adjustTo(obstacleHitbox);
	}

	h.moveX(5);
	if (h.leftCollisionWith(obstacleHitbox))
		state.movingRight = false;
	else if (state.jumpingRight && hitbox.inFrontOf(obstacleHitbox)) {
		state.movingRight = true;
		state.jumpingRight = false;
	}

	h.moveX(-10);
	if (h.rightCollisionWith(obstacleHitbox))
		state.movingLeft = false;
	else if (state.jumpingLeft && hitbox.inFrontOf(obstacleHitbox)) {
		state.movingLeft = true;
		state.jumpingLeft = false;
	}

	if (hitbox.downCollisionWith(obstacleHitbox)) {
		state.jumping = false;
		state.falling = true;

		obstacle.getsHit(state.big);
	}
}
void Player::collidesWithEnemy(Entity& enemy) {}
void Player::collidesWithPlayer(Entity& player) {}
	