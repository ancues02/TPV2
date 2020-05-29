#pragma once

#include <vector>

#include "BulletsSystem.h"
#include "CollisionSystem.h"
#include "FightersSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "RenderSystem.h"
#include "NetworkingSystem.h"
#include "SDLGame.h"

class StarWars {

public:
	StarWars(char* host, int port, const char* name);
	virtual ~StarWars();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void closeGame();

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;
	char* host_;
	const char* name_;
	int port_;
	NetworkingSystem *networkingSystem_;
	RenderSystem *renderSystem_;
	FightersSystem *fightersSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	BulletsSystem *bulletsSystem_;
	CollisionSystem *collisionSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

};
