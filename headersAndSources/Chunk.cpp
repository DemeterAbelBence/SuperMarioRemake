#pragma once

#include "Chunk.hpp"

void Chunk::groundCollision(Entity& entity) { entity.collidesWithObstacle(*ground); }
void Chunk::addMushroomUponObstacleActivation(Player& player, Obstacle* obstacle) {
	int x = obstacle->getHitbox().getX();
	int y;

	if (!player.isBig()) {
		y = obstacle->getHitbox().getY() - Mushroom().getHeight() - 10;
		Mushroom* mushroom = new Mushroom(x, y);
		enemies.insert(mushroom);
	}
	else {
		y = obstacle->getHitbox().getY() - Flower().getHeight() - 10;
		Flower* flower = new Flower(x, y);
		enemies.insert(flower);
	}
	obstacle->setActivated(false);
}
void Chunk::addGoombaUponObstacleActivation(Obstacle* obstacle) {
	int x = obstacle->getHitbox().getX();
	int y = obstacle->getHitbox().getY() + obstacle->getHitbox().getHeight() + 10;

	Goomba* goomba = new Goomba(x, y);
	enemies.insert(goomba);

	obstacle->setActivated(false);
}

Chunk::Chunk() {}
Chunk::Chunk(int offsetX, int offsetY) {
	ground->set(offsetX, offsetY);
}
Obstacle* Chunk::getGround() const { return ground; }
Collection<Obstacle> Chunk::getObstacles() const { return obstacles; }
Collection<Entity> Chunk::getEnemies() const { return enemies; }
void Chunk::set(int offsetX, int offsetY) {
	ground->set(offsetX, offsetY);
}
void Chunk::setY(int height) {
	ground->setY(height);
}
void Chunk::setGround(bool lava, bool pit, int offsetX, int offsetY) {
	if (pit) {
		ground = new Pit(offsetX, offsetY);
		return;
	}

	ground = new Dirt(offsetX, offsetY);
}

void Chunk::addEnemyWithOffset(Entity* entity) {
	entity->moveX(ground->getHitbox().getX());
	enemies.insert(entity);
}
void Chunk::addEnemyWithoutOffset(Entity* entity) { enemies.insertAsFirst(entity); }
void Chunk::addObstacleWithOffset(Obstacle* obstacle) {
	obstacle->moveX(ground->getHitbox().getX());
	obstacles.insert(obstacle);
}
bool Chunk::onChunk(const Entity& entity) const{
	int ex1 = entity.getHitbox().getX();
	int ex2 = entity.getHitbox().getX() + entity.getHitbox().getWidth();
	int gx1 = ground->getHitbox().getX();
	int gx2 = ground->getHitbox().getX() + ground->getHitbox().getWidth();
	return (ex1 >= gx1 && ex2 <= gx2);
}
bool Chunk::onChunkEdge(const Entity& entity) const {
	int ex1 = entity.getHitbox().getX();
	int ex2 = entity.getHitbox().getX() + entity.getHitbox().getWidth();
	int cx = ground->getHitbox().getX();
	return ex1 < cx && ex2 > cx;
}
void Chunk::playerUpdate(Player& player, bool currentChunk) {
	int size = obstacles.getSize();
	Array<Obstacle*> destroyedObstacles;

	player.setFloating(true);
	groundCollision(player);

	if (currentChunk) {
		for (int i = 0; i < size; ++i) {
			Obstacle* o = obstacles.get(i);
			player.collidesWithObstacle(*o);

			obstacles[i]->update();
			if (o->isDestroyed())
				destroyedObstacles.add(o);

			if (o->spawnsMushroom())
				addMushroomUponObstacleActivation(player, o);

			if (o->spawnsGoomba())
				addGoombaUponObstacleActivation(o);
		}

		size = destroyedObstacles.getSize();
		for (int i = 0; i < size; ++i)
			obstacles.remove(destroyedObstacles.get(i), true);

		if (player.isFloating() && !player.isJumping() && !player.isFalling())
			player.setFalling(true);
	}

	if (player.isShooting()) {
		int x = player.getHitbox().getX();
		int y = player.getHitbox().getY() + 20;
		int w = player.getHitbox().getWidth();
		bool shootingLeft = player.isFacingLeft();
		FireBall* fireBall;

		if(shootingLeft)
			fireBall = new FireBall(x, y, shootingLeft);
		else
			fireBall = new FireBall(x + w, y, shootingLeft);

		enemies.insertAsFirst(fireBall);
		player.setShooting(false);
	}
}
void Chunk::entityObstaclesCollisionUpdate(Entity& entity, bool currentChunk) {
	int size = obstacles.getSize();
	entity.setFloating(true);
	groundCollision(entity);

	if (currentChunk) {
		for (int i = 0; i < size; ++i)
			entity.collidesWithObstacle(*obstacles.get(i));

		if (entity.isFloating() && !entity.isJumping() && !entity.isFalling())
			entity.setFalling(true);
	}
}
void Chunk::entityEntitiesCollisionUpdate(Entity& entity) {
	int size = enemies.getSize();

	for (int i = 0; i < size; ++i)
		entity.collidesWithEnemy(*enemies[i]);
}
void Chunk::enemyUpdate(Chunk& leftChunk, Chunk& rightChunk, Player& player) {
	int size = enemies.getSize();

	Array<Entity*> enemiesEnteringLeftChunk;
	Array<Entity*> enemiesEnteringRightChunk;
	Array<Entity*> deadEntities;

	Hitbox h;

	for (int i = 0; i < size; ++i) {
		Entity* e = enemies[i];

		e->update();
		e->collidesWithPlayer(player);
		entityObstaclesCollisionUpdate(*e, true);
		entityEntitiesCollisionUpdate(*e);
		leftChunk.groundCollision(*e);
		rightChunk.groundCollision(*e);

		h = e->getHitbox();
		if (h.getX() + h.getWidth() < ground->getHitbox().getX())
			enemiesEnteringLeftChunk.add(e);
				
		if (h.getX() > ground->getHitbox().getX() + ground->getHitbox().getWidth())
			enemiesEnteringRightChunk.add(e);

		if (e->isDead())
			deadEntities.add(e);
	}

	size = enemiesEnteringLeftChunk.getSize();
	for (int i = 0; i < size; ++i) {
		Entity* e = enemiesEnteringLeftChunk[i];
		leftChunk.addEnemyWithoutOffset(e);
		enemies.remove(e, false);
	}
		
	size = enemiesEnteringRightChunk.getSize();
	for (int i = 0; i < size; ++i) {
		Entity* e = enemiesEnteringRightChunk[i];
		rightChunk.addEnemyWithoutOffset(e);
		enemies.remove(e, false);
	}

	size = deadEntities.getSize();
	for (int i = 0; i < size; ++i)
		enemies.remove(deadEntities.get(i), true);
}
void Chunk::enemyUpdate(Chunk& adjacentChunk, Player& player) {
	int size = enemies.getSize();

	Array<Entity*> enemiesEnteringRightChunk;
	Array<Entity*> deadEntities;

	Hitbox h;

	for (int i = 0; i < size; ++i) {
		Entity* e = enemies[i];

		e->update();
		e->collidesWithPlayer(player);
		entityObstaclesCollisionUpdate(*e, true);
		entityEntitiesCollisionUpdate(*e);
		adjacentChunk.groundCollision(*e);

		if (h.getX() > ground->getHitbox().getX() + ground->getHitbox().getWidth())
			enemiesEnteringRightChunk.add(e);

		if (e->isDead())
			deadEntities.add(e);
	}

	size = enemiesEnteringRightChunk.getSize();
	for (int i = 0; i < size; ++i) {
		Entity* e = enemiesEnteringRightChunk[i];
		adjacentChunk.addEnemyWithoutOffset(e);
		enemies.remove(e, false);
	}

	size = deadEntities.getSize();
	for (int i = 0; i < size; ++i)
		enemies.remove(deadEntities.get(i), true);
}
void Chunk::enemyUdateAsLeftChunk(Chunk& chunk, Player& player) {
	int size = enemies.getSize();
	Array<Entity*> deadEntities;

	Hitbox h;

	for (int i = 0; i < size; ++i) {
		Entity* e = enemies[i];

		e->update();
		e->collidesWithPlayer(player);
		entityObstaclesCollisionUpdate(*e, true);
		entityEntitiesCollisionUpdate(*e);

		if (h.getX() > ground->getHitbox().getX() + ground->getHitbox().getWidth())
			deadEntities.add(e);

		if (e->isDead())
			deadEntities.add(e);
	}
}

void Chunk::moveX(int value) {
	int e = enemies.getSize();
	for (int i = 0; i < e; ++i) {
		enemies[i]->moveX(value);
	}

	int o = obstacles.getSize();
	for (int i = 0; i < o; ++i) {
		obstacles[i]->moveX(value);
	}

	ground->moveX(value);
}
void Chunk::moveY(int value) {
	int e = enemies.getSize();
	for (int i = 0; i < e; ++i) {
		enemies[i]->moveY(value);
	}

	int o = obstacles.getSize();
	for (int i = 0; i < o; ++i) {
		obstacles[i]->moveY(value);
	}

	ground->moveY(value);
}
void Chunk::draw(const SDL::Manager& manager) const{
	int e = enemies.getSize();
	for (int i = 0; i < e; ++i) {
		enemies[i]->draw(manager);
	}

	int o = obstacles.getSize();
	for (int i = 0; i < o; ++i) {
		obstacles[i]->draw(manager);
	}

	ground->draw(manager);
}

Chunk::~Chunk() {
	delete ground;
}
	