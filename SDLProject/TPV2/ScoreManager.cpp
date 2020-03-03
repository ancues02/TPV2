#include "ScoreManager.h"

ScoreManager::ScoreManager() :
		Component(ecs::ScoreManager), //
		state(Stop), //
		score(0) //
{
}

ScoreManager::~ScoreManager() {
}

