#pragma once

#include "Dirt.hpp"

class Pit : public Obstacle{

private:
	static int width;
	static int height;
	static SDL::Image image;

public:
	Pit();
	Pit(int x, int y);
	int getWidth() const;

	void update() override;
	bool spawnsGoomba() const override;
	bool spawnsMushroom() const override;
	void set(int x, int y);
	void setImage(const char* fileName) override;
	void draw(const SDL::Manager& manager) const override;
	void getsHit(bool canBeDestroyed) override;
};
