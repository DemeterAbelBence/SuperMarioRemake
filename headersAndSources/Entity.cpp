#pragma once

#include "Entity.hpp"

Entity::Entity() : movementTimer(movementTimerPeriod) {}

void Entity::setFalling(bool value) { state.falling = value; }
void Entity::setJumping(bool value) { state.jumping = value; }
void Entity::setMovingRight(bool value) { state.movingRight = value; }
void Entity::setMovingLeft(bool value) { state.movingLeft = value; }
void Entity::setJumpingRight(bool value) { state.jumpingRight = value; }
void Entity::setJumpingLeft(bool value) { state.jumpingLeft = value; }
void Entity::setFloating(bool value) { state.floating = value; }
void Entity::setFacingLeft(bool value) { state.facingLeft = value; }
void Entity::setFacingRight(bool value) { state.facingRight = value; }
void Entity::setStanding(bool value) { state.standing = value; }
void Entity::setHit(bool value) { state.hit = value; }
void Entity::setDead(bool value) { state.dead = value; }
void Entity::setBig(bool value) { state.big = value; }
void Entity::setAblaze(bool value) { state.ablaze = value; }
void Entity::setShooting(bool value) { state.shooting = value; }
void Entity::setJumpHeight(int value) { jumpHeight = value; }
void Entity::setJumpLimit(int value) { jumpLimit = value; }
void Entity::setJumpSpeed(int value) { jumpSpeed = value; }
void Entity::setMoveSpeed(int value) { moveSpeed = value; }
void Entity::setImageIndex(int value) { imageIndex = value; }

bool Entity::isJumping() const { return state.jumping; }
bool Entity::isFalling() const { return state.falling; }
bool Entity::isMovingRight() const { return state.movingRight; }
bool Entity::isMovingLeft() const { return state.movingLeft; }
bool Entity::isFloating() const { return state.floating; }
bool Entity::isFacingLeft() const { return state.facingLeft; }
bool Entity::isFacingRight() const { return state.facingRight; }
bool Entity::isStanding() const { return state.standing; }
bool Entity::isHit() const { return state.hit; }
bool Entity::isDead() const { return state.dead; }
bool Entity::isBig() const { return state.big; }
bool Entity::isAblaze() const { return state.ablaze; }
bool Entity::isShooting() const { return state.shooting; }
int Entity::getJumpHeight() const { return jumpHeight; }
int Entity::getJumpLimit() const { return jumpLimit; }
int Entity::getMoveSpeed() const { return moveSpeed; }
int Entity::getJumpSpeed() const { return jumpSpeed; }
int Entity::getFallSpeed() const { return fallSpeed; }
int Entity::getImageIndex() const { return imageIndex; }
Hitbox Entity::getHitbox() const { return hitbox; }

void Entity::shortenMovementTimerPeriod() {
	int newPeriod = movementTimerPeriod / 2;
	movementTimer.set(newPeriod);
}
void Entity::setMovementTimerPeriod() { movementTimer.set(movementTimerPeriod); }
void Entity::resetMovementTimer() { movementTimer.reset(); }
void Entity::changeHitboxHeight(int value) {
	if (!state.big) {
		int height = hitbox.getHeight();
		int newHeight = height + value;
		hitbox.setHeight(newHeight);
		hitbox.moveY(-value);
	}
}
void Entity::jump(int value) {
	int y = hitbox.getY();
	if (y < jumpHeight) {
		state.falling = true;
		state.jumping = false;
		return;
	}
	hitbox.setY(y - value);
}
void Entity::fall(int value) {
	int y = hitbox.getY();
	hitbox.setY(y + value);
}
void Entity::moveX(int value) { hitbox.moveX(value); }
void Entity::moveY(int value) { hitbox.moveY(value); }
	