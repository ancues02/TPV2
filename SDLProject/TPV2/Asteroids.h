#pragma once

#include <vector>

#include "Manager.h"
#include "SDLGame.h"

#include "GameCtrl.h"
#include "GameLogic.h"
#include "InputHandler.h"
#include "FighterCtrl.h"
#include "VelocityVectorViewer.h"
#include "PaddleMouseCtrl.h"
#include "FighterMotion.h"
#include "Rectangle.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "SimpleMoveBahviour.h"
#include "Transform.h"

#include "FighterViewer.h"
#include "Health.h"
#include "Gun.h"
#include "SDL_macros.h"
#include "AsteroidPool.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"
#include "BulletsPool.h"
#include "BulletsMotion.h"
#include "BulletsViewer.h"


class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();
	void handleInput();
	void update();
	void render();

	SDLGame* game_;
	EntityManager* entityManager_;
	bool exit_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
