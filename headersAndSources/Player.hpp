#pragma once
#include "Entity.hpp"

class Player : public Entity{
	static int width;
	static int height;
	static Array<SDL::Image> images;

	const int defaultSpeed = 3;
	const int sprintSpeed = 5;

	Timer vulnerabilityTimer;

public:
	Player();

	void accelerate();
	void resetSpeed();
	void setPosition(int x, int y);

	void addImage(const char* imageName) override;
	void resetImages() override;
	void update() override;
	void draw(const SDL::Manager& manager) const override;
	void collidesWithObstacle(Obstacle& obstacle) override;
	void collidesWithEnemy(Entity& enemy) override;
	void collidesWithPlayer(Entity& player) override;
};

