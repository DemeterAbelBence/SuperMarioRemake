#pragma once

#include "FireBall.hpp"

int FireBall::width = 20;
int FireBall::height = 20;
Array<SDL::Image> FireBall::images = Array<SDL::Image>();

FireBall::FireBall() {}
FireBall::FireBall(int x, int y, bool goingLeft) {
	if (goingLeft) {
		state.movingLeft = true;
		state.movingRight = false;
	}
	else {
		state.movingLeft = false;
		state.movingRight = true;
	}
	state.falling = true;
	state.jumping = false;
	state.floating = false;
	state.standing = false;
	state.facingRight = false;
	state.facingLeft = false;
	state.hit = false;
	state.dead = false;

	jumpHeight = 0;
	moveSpeed = 8;
	jumpSpeed = 6;
	fallSpeed = 9;
	imageIndex = 0;

	hitbox.resize(x, y, width, height);
}
int FireBall::getHeight() const { return height; }
void FireBall::addImage(const char* imageName) {
	SDL::Image image(imageName);
	images.add(image);
}
void FireBall::resetImages() {}
void FireBall::draw(const SDL::Manager& manager) const { images[imageIndex].draw(manager, hitbox); }
void FireBall::update() {
	if (state.jumping)
		jump(jumpSpeed);

	if (state.falling)
		fall(fallSpeed);

	if (state.movingLeft)
   		moveX(-moveSpeed);

	if (state.movingRight)
		moveX(moveSpeed);
}
void FireBall::collidesWithObstacle(Obstacle& obstacle) {
	Hitbox obstacleHitbox = obstacle.getHitbox();
		
	if (hitbox.upCollisionWith(obstacleHitbox)) {
		state.jumping = true;
		state.falling = false;
		jumpHeight = obstacleHitbox.getY() - 60;
	}

	if (hitbox.leftCollisionWith(obstacleHitbox))
		state.dead = true;

	if (hitbox.rightCollisionWith(obstacleHitbox))
		state.dead = true;	
}
void FireBall::collidesWithEnemy(Entity& enemy) {
	Hitbox enemyHitbox = enemy.getHitbox();

	if (hitbox.collidesWith(enemyHitbox)) {
		state.dead = true;
		enemy.setDead(true);
	}
}
void FireBall::collidesWithPlayer(Entity& player) {}
	