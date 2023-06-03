#pragma once

#include "Chunk.hpp"
#include "Background.hpp"

template <int size>
class Map {

private:
	const int initialHeight = 500;

	int currentChunk;

	Chunk chunks[size];
	Background<5> background;

private:
	int getHigherChunk(int index) const {
		int cy1 = chunks[index].getGround()->getHitbox().getY();
		int cy2 = chunks[index - 1].getGround()->getHitbox().getY();

		if (cy1 < cy2) {
			return index;
		}
		else {
			return index - 1;
		}
	}
	int getCurrentChunk(const Entity& entity) const{
		for (int i = 0; i < size; ++i) {
			if (chunks[i].onChunk(entity)) {
				return i;
			}
			else {
				if(chunks[i].onChunkEdge(entity))
					return getHigherChunk(i);
			}
		}
		throw "No chunk found exception!";
	}

public:
	Map() {}

	void setup1() {
		background.set("pngs\\sky.png", -500, 0, 1200, 800);

		int width = Dirt().getWidth();
		int offsetX = -width;

		chunks[0].setGround(false, false, offsetX + 0 * width, initialHeight);
		chunks[1].setGround(false, false, offsetX + 1 * width, initialHeight);
		chunks[2].setGround(false, false, offsetX + 2 * width, initialHeight);
		chunks[3].setGround(false, true, offsetX + 3 * width, 800);
		chunks[4].setGround(false, false, offsetX + 4 * width, initialHeight);
		chunks[5].setGround(false, false, offsetX + 5 * width, initialHeight);
		chunks[6].setGround(false, false, offsetX + 6 * width, initialHeight);
		chunks[7].setGround(false, true, offsetX + 7 * width, initialHeight);
		chunks[8].setGround(false, false, offsetX + 8 * width, initialHeight);
		chunks[9].setGround(false, false, offsetX + 9 * width, initialHeight);

		//chunk 0
		chunks[0].setY(300);
		InvisibleWall* iw0 = new InvisibleWall(0, 0);
		chunks[0].addObstacleWithOffset(iw0);
		

		//chunk 1
		chunks[1].setY(400);
		Pipe* p1 = new Pipe(100, 250);
		chunks[1].addObstacleWithOffset(p1);
		PiranhaPlant* pp1 = new PiranhaPlant(110, 190, 50);
		chunks[1].addEnemyWithOffset(pp1);


		Spawner* s1 = new Spawner(600, 0);
		chunks[1].addObstacleWithOffset(s1);
		

		//chunk 2
		Brick* b2;
		b2 = new Brick(150, 300);
		chunks[2].addObstacleWithOffset(b2);

		LuckyBrick* l2 = new LuckyBrick(200, 300);
		chunks[2].addObstacleWithOffset(l2);
		
		b2 = new Brick(250, 300);
		chunks[2].addObstacleWithOffset(b2);

		//chunk 3
		Brick* b3;
		for (int i = 0; i < 3; ++i) {
			b3 = new Brick(200 + 50 * i, 400);
			chunks[3].addObstacleWithOffset(b3);
		}

		LuckyBrick* l3 = new LuckyBrick(250, 220);
		chunks[3].addObstacleWithOffset(l3);

		for (int i = 0; i < 3; ++i) {
			b3 = new Brick(500 + 50 * i, 300);
			chunks[3].addObstacleWithOffset(b3);
		}
		

		//chunk 4
		chunks[4].setY(350);

		Goomba* goomba4 = new Goomba(200, 100);
		chunks[4].addEnemyWithOffset(goomba4);

		goomba4 = new Goomba(290, 100);
		chunks[4].addEnemyWithOffset(goomba4);

		goomba4 = new Goomba(540, 100);
		chunks[4].addEnemyWithOffset(goomba4);

		goomba4 = new Goomba(260, 100);
		chunks[4].addEnemyWithOffset(goomba4);

		//chunk 5
		chunks[5].setY(400);
		
		Pipe* p5 = new Pipe(300, 300);
		chunks[5].addObstacleWithOffset(p5);

		p5 = new Pipe(400, 250);
		chunks[5].addObstacleWithOffset(p5);
		PiranhaPlant* pp5 = new PiranhaPlant(410, 190, 30);
		chunks[5].addEnemyWithOffset(pp5);

		Goomba* goomba5 = new Goomba(500, 100);
		chunks[5].addEnemyWithOffset(goomba5);

		p5 = new Pipe(650, 250);
		chunks[5].addObstacleWithOffset(p5);
		pp5 = new PiranhaPlant(660, 190, 0);
		chunks[5].addEnemyWithOffset(pp5);

		//chunk 6
		chunks[6].setY(400);

		//chunk 7
		chunks[7].setY(800);
		Brick* b7;
		for (int i = 0; i < 3; ++i) {
			b7 = new Brick(100 + 50 * i, 350);
			chunks[7].addObstacleWithOffset(b7);
		}
		for (int i = 0; i < 2; ++i) {
			b7 = new Brick(500 + 50 * i, 350);
			chunks[7].addObstacleWithOffset(b7);
		}

		//chunk 8

		//chunk 9
		InvisibleWall* iw9 = new InvisibleWall(600, 0);
		chunks[9].addObstacleWithOffset(iw9);

		moveX(100);
	}
	void update(Player& player) {	
		currentChunk = getCurrentChunk(player);

		//current chunk update
		chunks[currentChunk].playerUpdate(player, true);
		chunks[currentChunk].entityEntitiesCollisionUpdate(player);
		if (currentChunk >= 0 && currentChunk <= size - 1) {
			if (currentChunk > 0) {
				chunks[currentChunk].enemyUpdate(chunks[currentChunk - 1], chunks[currentChunk + 1], player);
			}
			else {
				chunks[currentChunk].enemyUpdate(chunks[currentChunk + 1], player);
			}
		}
		

		//left chunk update
		if (currentChunk > 0 && currentChunk < size) {
			chunks[currentChunk - 1].entityObstaclesCollisionUpdate(player, false);
			if (currentChunk > 1) {
				chunks[currentChunk - 1].enemyUpdate(chunks[currentChunk - 2], chunks[currentChunk], player);
			}
			else {
				chunks[currentChunk - 1].enemyUpdate(chunks[currentChunk], player);
			}

		}

		//right chunk update
		if (currentChunk < size - 1) {
			chunks[currentChunk + 1].entityObstaclesCollisionUpdate(player, false);
			if (currentChunk < size - 1) {
				chunks[currentChunk + 1].enemyUpdate(chunks[currentChunk], chunks[currentChunk + 2], player);
			}
			else {
				chunks[currentChunk + 1].enemyUpdate(chunks[currentChunk], player);
			}
		}
	}
	void moveX(int value) {
		for (int i = 0; i < size; ++i) {
			chunks[i].moveX(value);
		}

		background.move(value/2);
	}
	void moveY(int value) {
		for (int i = 0; i < size; ++i) {
			chunks[i].moveY(value);
		}
	}
	void draw(const SDL::Manager& manager, const Player& player) const{
		background.draw(manager);
		chunks[currentChunk].draw(manager);

		if (currentChunk > 0)
			chunks[currentChunk - 1].draw(manager);

		if (currentChunk < size - 1)
			chunks[currentChunk + 1].draw(manager);

	}
};