#pragma once

#include "Collection.hpp"
#include "Entity.hpp"
#include "Obstacle.hpp"
#include "Player.hpp"
#include "Goomba.hpp"
#include "Mushroom.hpp"
#include "PiranhaPlant.hpp"
#include "Flower.hpp"
#include "FireBall.hpp"
#include "Dirt.hpp"
#include "Pit.hpp"
#include "Brick.hpp"
#include "LuckyBrick.hpp"
#include "Pipe.hpp"
#include "InvisibleWall.hpp"
#include "Spawner.hpp"

class Chunk{

private:
	Collection<Entity> enemies;
	Collection<Obstacle> obstacles;
	Obstacle* ground;

private:
	void groundCollision(Entity& entity);
	void addMushroomUponObstacleActivation(Player& player, Obstacle* obstacle);
	void addGoombaUponObstacleActivation(Obstacle* obstacle);

public:
	Chunk();
	Chunk(int offsetX, int offsetY);

	Obstacle* getGround() const;
	Collection<Obstacle> getObstacles() const;
	Collection<Entity> getEnemies() const;

	void set(int offsetX, int offsetY);
	void setY(int height);
	void setGround(bool lava, bool pit, int offsetX, int offsetY);

	void addEnemyWithOffset(Entity* entity);
	void addEnemyWithoutOffset(Entity* entity);
	void addObstacleWithOffset(Obstacle* obstacle);

	bool onChunk(const Entity& entity) const;
	bool onChunkEdge(const Entity& entity) const;
	void playerUpdate(Player& player, bool currentChunk);
	void entityObstaclesCollisionUpdate(Entity& entity, bool currentChunk);
	void entityEntitiesCollisionUpdate(Entity& entity);
	void enemyUpdate(Chunk& leftChunk, Chunk& rightChunk, Player& player);
	void enemyUpdate(Chunk& adjacentChunk, Player& player);
	void enemyUdateAsLeftChunk(Chunk& chunk, Player& player);

	void moveX(int value);
	void moveY(int value);
	void draw(const SDL::Manager& manager) const;

	~Chunk();
};
