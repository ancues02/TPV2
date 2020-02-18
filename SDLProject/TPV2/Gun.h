#pragma once
#include "Component.h"
#include  "Transform.h"

class Gun : public Component
{
public:
	Gun();
	Gun(SDL_Keycode shoot);
	void init() override;
	void update() override;
	virtual ~Gun();
private:
	SDL_Keycode shoot;
	Transform* tr_;
};

