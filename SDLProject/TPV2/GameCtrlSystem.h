#pragma once

#include "System.h"

struct GameState;

class GameCtrlSystem: public System {
public:

	GameCtrlSystem();

	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;

private:
	void startGame();

	GameState *gameState_;

	// TODO: these methods should go private
	void onPacManDeath();
	void onNoMoreFood();
};

