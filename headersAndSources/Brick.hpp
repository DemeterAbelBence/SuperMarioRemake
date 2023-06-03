#pragma once
#include "Obstacle.hpp"

class Brick : public Obstacle{

private:
	static int width;
	static int height;
	static SDL::Image image;

public:
	Brick();
	Brick(int x, int y);
	void set(int x, int y);

	void update() override;
	bool spawnsGoomba() const override;
	bool spawnsMushroom() const override;
	int getWidth() const override;
	void setImage(const char* fileName) override;
	void draw(const SDL::Manager& manager) const override;
	void getsHit(bool canBeDestroyed) override;
};
