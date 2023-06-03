#pragma once

#include "Obstacle.hpp"
#include "Timer.hpp"

class Spawner : public Obstacle {

private:
	static int width;
	static int height;
	static SDL::Image image;

	static const int spawnPeriod = 150;

	Timer spawnTimer;

public:
	Spawner();
	Spawner(int x, int y);
	void set(int x, int y);

	void update();
	bool spawnsGoomba() const override;
	bool spawnsMushroom() const override;
	int getWidth() const override;
	void setImage(const char* fileName) override;
	void draw(const SDL::Manager& manager) const override;
	void getsHit(bool canBeDestroyed) override;
};
