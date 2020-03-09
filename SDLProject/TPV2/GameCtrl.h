#pragma once

#include "Component.h"
#include "ScoreManager.h"
#include "Transform.h"
#include "Health.h"
#include "AsteroidPool.h"

class GameCtrl: public Component {
public:
	GameCtrl(AsteroidPool* ast_pool,  Health *health);
	virtual ~GameCtrl();
	void init() override;
	void update() override;
	void draw() override;
private:
	AsteroidPool* ast_pool;
	Health* health;
	ScoreManager *scoreManager_;
};