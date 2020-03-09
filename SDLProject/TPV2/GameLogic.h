#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "AsteroidPool.h"
#include "BulletsPool.h"
#include "Health.h"

class GameLogic: public Component {
public:
	GameLogic(Transform* fighterTR_, AsteroidPool* ast_pool, BulletsPool* bullet_pool, Health* fighterH_);
	virtual ~GameLogic();
	void init() override;
	void update() override;
private:
	Transform* fighterTR_;
	AsteroidPool* ast_pool;
	BulletsPool* bullet_pool;
	Health* fighterH_;
	ScoreManager *scoreManager_;
};