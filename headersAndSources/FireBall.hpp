#pragma once
#include "Entity.hpp"

class FireBall : public Entity{

private:
	static int width;
	static int height;
	static Array<SDL::Image> images;

public:
	FireBall();
	FireBall(int x, int y, bool goingLeft);
	int getHeight() const;
	void addImage(const char* imageName) override;
	void resetImages() override;
	void draw(const SDL::Manager& manager) const override;
	void update() override;
	void collidesWithObstacle(Obstacle& obstacle) override;
	void collidesWithEnemy(Entity& enemy) override;
	void collidesWithPlayer(Entity& player) override;
};
