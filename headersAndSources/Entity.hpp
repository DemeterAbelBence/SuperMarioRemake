#pragma once

#include "Hitbox.hpp"
#include "SDLhandling.hpp"
#include "State.hpp"
#include "Array.hpp"
#include "Obstacle.hpp"
#include "Timer.hpp"

class Entity{

protected:
	static const int movementTimerPeriod = 20;

	int jumpHeight;
	int jumpLimit;
	int moveSpeed;
	int jumpSpeed;
	int fallSpeed;
	int imageIndex;

	State state;
	Hitbox hitbox;
	Timer movementTimer;

public:
	Entity();

	void setFalling(bool value);
	void setJumping(bool value);
	void setMovingRight(bool value);
	void setMovingLeft(bool value);
	void setJumpingRight(bool value);
	void setJumpingLeft(bool value);
	void setFloating(bool value);
	void setFacingLeft(bool value);
	void setFacingRight(bool value);
	void setStanding(bool value);
	void setHit(bool value);
	void setDead(bool value);
	void setBig(bool value);
	void setAblaze(bool value);
	void setShooting(bool value);
	void setJumpHeight(int value);
	void setJumpLimit(int value);
	void setJumpSpeed(int value);
	void setMoveSpeed(int value);
	void setImageIndex(int value);

	bool isJumping() const;
	bool isFalling() const;
	bool isMovingRight() const;
	bool isMovingLeft() const;
	bool isFloating() const;
	bool isFacingLeft() const;
	bool isFacingRight() const;
	bool isStanding() const;
	bool isHit() const;
	bool isDead() const;
	bool isBig() const;
	bool isAblaze() const;
	bool isShooting() const;
	int getJumpHeight() const;
	int getJumpLimit() const;
	int getMoveSpeed() const;
	int getJumpSpeed() const;
	int getFallSpeed() const;
	int getImageIndex() const;
	
	Hitbox getHitbox() const;

	void shortenMovementTimerPeriod();
	void setMovementTimerPeriod();
	void resetMovementTimer();
	void changeHitboxHeight(int value);
	void jump(int value);
	void fall(int value);
	void moveX(int value);
	void moveY(int value);

	virtual void addImage(const char* imageName) = 0;
	virtual void resetImages() = 0;
	virtual void draw(const SDL::Manager& manager) const = 0;
	virtual void update() = 0;
	virtual void collidesWithObstacle(Obstacle& obstacle) = 0;
	virtual void collidesWithEnemy(Entity& enemy) = 0;
	virtual void collidesWithPlayer(Entity& player) = 0;
};
