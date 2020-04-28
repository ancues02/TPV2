#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidSystem.h"
#include "GameState.h"
#include "BulletsSystem.h"
#include "FighterSystem.h"

class GameCtrlSystem: public System {
public:

	GameCtrlSystem() :
		System(ecs::_sys_GameCtrl) {
	}

	void init() override;

	void update() override;
	// - actualizar los componentes correspondientes (Score, Heath, GameState, �).
	void onFighterDeath();
	
	
	void onAsteroidsExtenction();
};

