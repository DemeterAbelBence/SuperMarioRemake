#pragma once

#include <math.h>

class Hitbox{

private:
	int x;
	int y;

	int width;
	int height;

public:
	Hitbox();
	Hitbox(int x0, int y0, int w, int h);

	void setX(int x0);
	void setY(int y0);
	void setWidth(int w);
	void setHeight(int h);
	void resize(int x0, int y0, int w, int h);

	int getX() const;
	int getY() const;
	int getWidth() const;
	int getHeight() const;

	void operator=(const Hitbox& H);
	void extend(int value);
	bool leftCollisionWith(const Hitbox& h) const;
	bool rightCollisionWith(const Hitbox& h) const;
	bool upCollisionWith(const Hitbox& h) const;
	bool downCollisionWith(const Hitbox& h) const;
	bool collidesWith(const Hitbox& h) const;
	bool inFrontOf(const Hitbox& h) const;
	void adjustTo(const Hitbox& h);
	bool containsCoordinate(int x0, int y0) const;
	void moveX(int value);
	void moveY(int value);
};
