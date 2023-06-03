#pragma once

#include "Game.hpp"

void Game::handleEvents() {			
	int eventType = userEvent.getNewEvent(mouse);

	if (!menu.isVisible()) {
		switch (eventType) {

		case KEYDOWN_A:
			player.setMovingLeft(true);
			player.setFacingLeft(true);
			player.setFacingRight(false);
			player.setStanding(false);
			break;

		case KEYDOWN_W:
			if (!player.isFalling())
				player.setJumping(true);

			player.setStanding(false);
			break;

		case KEYDOWN_D:
			player.setMovingRight(true);
			player.setFacingLeft(false);
			player.setFacingRight(true);
			player.setStanding(false);
			break;

		case KEYDOWN_SHIFT:
			player.accelerate();
			player.shortenMovementTimerPeriod();
			break;

		case KEYDOWN_ESC:
			running = false;
			break;

		case KEYUP_A:
			player.setMovingLeft(false);
			player.setJumpingLeft(false);
			if (!player.isJumping() && !player.isFalling())
				player.setStanding(true);
			break;

		case KEYUP_D:
			player.setMovingRight(false);
			player.setJumpingRight(false);
			if (!player.isJumping() && !player.isFalling())
				player.setStanding(true);
			break;

		case KEYUP_SHIFT:
			player.resetSpeed();
			player.setMovementTimerPeriod();
			break;

		case KEYUP_SPACE:
			if (player.isAblaze())
				player.setShooting(true);
			break;

		case NOTHING:
			break;
		}
	}
	else menu.update(mouse.x, mouse.y, mouse.leftClick, &running);
	
	mouse.leftClick = false;
}
Game::Game() { map = new Map<mapSize>(); }
Game::Game(const SDL::Manager& manager) {
	player.setPosition(350, 100);

	player.addImage("pngs\\mario_pngs\\movingRight1.png");
	player.addImage("pngs\\mario_pngs\\movingRight2.png");
	player.addImage("pngs\\mario_pngs\\movingRight3.png");
	player.addImage("pngs\\mario_pngs\\movingLeft1.png");
	player.addImage("pngs\\mario_pngs\\movingLeft2.png");
	player.addImage("pngs\\mario_pngs\\movingLeft3.png");
	player.addImage("pngs\\mario_pngs\\standingLeft.png");
	player.addImage("pngs\\mario_pngs\\standingRight.png");
	player.addImage("pngs\\mario_pngs\\jumpLeft.png");
	player.addImage("pngs\\mario_pngs\\jumpRight.png");

	Goomba().addImage("pngs\\goomba_pngs\\goomba1.png");
	Goomba().addImage("pngs\\goomba_pngs\\goomba2.png");
	Goomba().addImage("pngs\\goomba_pngs\\deadGoomba.png");

	Mushroom().addImage("pngs\\mushroom_pngs\\mushroom1.png");
	Mushroom().addImage("pngs\\mushroom_pngs\\mushroom2.png");

	PiranhaPlant().addImage("pngs\\plant_pngs\\plant1.png");
	PiranhaPlant().addImage("pngs\\plant_pngs\\plant2.png");

	Flower().addImage("pngs\\flower_pngs\\flower1.png");
	Flower().addImage("pngs\\flower_pngs\\flower2.png");

	Dirt().setImage("pngs\\obstacle_pngs\\ground.png");
	Brick().setImage("pngs\\obstacle_pngs\\brick.png");
	Pipe().setImage("pngs\\obstacle_pngs\\pipeUp.png");
	Spawner().setImage("pngs\\obstacle_pngs\\pipeDown.png");

	FireBall().addImage("pngs\\fireBall_pngs\\fireBall.png");

	map = new Map<mapSize>();
	map->setup1();
}
void Game::update(const SDL::Manager& manager) {
	handleEvents();
	map->update(player);
	player.update();
	if (player.isDead())
		std::cout << ":( ";

	if (player.isMovingLeft())
		map->moveX(player.getMoveSpeed());

	if (player.isMovingRight())
		map->moveX(-player.getMoveSpeed());	

	if (player.isJumping())
		player.jump(player.getJumpSpeed());

	if (player.isFalling())
		player.fall(player.getFallSpeed());

	if (player.isDead()) {
		delete map;
		map = new Map<mapSize>();
		map->setup1();

		player.setPosition(350, 100);
		map->update(player);
		player.setDead(false);
		player.setAblaze(false);
		player.setBig(false);
	}
}
bool Game::isRunning() const { return running; }
void Game::draw(const SDL::Manager& manager) const{
	manager.clearFrame();
	map->draw(manager, player);
	player.draw(manager);
	if (menu.isVisible())
		menu.draw(manager);

	manager.renderFrame();
}
Game::~Game() { delete map; }
	