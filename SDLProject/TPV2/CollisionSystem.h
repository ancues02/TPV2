#pragma once

#include "System.h"

class CollisionSystem: public System {
public:
	CollisionSystem();
	virtual ~CollisionSystem();
	void recieve(const msg::Message& msg) override;
	void update() override;
};

