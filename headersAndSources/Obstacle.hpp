#pragma once

#include "Hitbox.hpp"
#include "SDLhandling.hpp"

class Obstacle{

protected:
	Hitbox hitbox;

	bool destroyed;
	bool activated;
	bool deadly;

public:
	Obstacle();
	Obstacle(int x, int y, int w, int h);
	void setY(int value);
	void setActivated(int value);
	void setDeadly(bool value);
	bool isDestroyed() const;
	bool isActivated() const;
	bool isDeadly() const;
	Hitbox getHitbox() const;
	void moveX(int value);
	void moveY(int value);
	
	virtual void update() = 0;
	virtual bool spawnsGoomba() const = 0;
	virtual bool spawnsMushroom() const = 0;
	virtual void set(int x, int y) = 0;
	virtual int getWidth() const = 0;
	virtual void setImage(const char* fileName) = 0;
	virtual void draw(const SDL::Manager& manager) const = 0;
	virtual void getsHit(bool canBeDestroyed) = 0;
};
