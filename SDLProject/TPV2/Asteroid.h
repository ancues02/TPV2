#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "FigtherGunSystem.h"
#include "RenderSystem.h"
#include "SDLGame.h"
#include "StarsSystem.h"
#include "AsteroidSystem.h"

class Asteroid {

public:
	Asteroid();
	virtual ~Asteroid();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	void addStars(std::size_t n);

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;

	RenderSystem *renderSystem_;
	AsteroidSystem*asteroidSystem_;
	FighterSystem*fighterSystem_;
	CollisionSystem *collisionSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	FigtherGunSystem* fighterGunSystem_;
	BulletsSystem* bulletSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
