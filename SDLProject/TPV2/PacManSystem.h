#pragma once

#include "System.h"
#include "Transform.h"
#include "Entity.h"

class PacManSystem: public System {
public:
	PacManSystem();
	void init() override;
	void update() override;
	void recieve(const msg::Message& msg) override;

private:
	Entity *pacman_;
	Transform *tr_;
	// TODO: these methods should go private
	void resetPacManPosition();
};

