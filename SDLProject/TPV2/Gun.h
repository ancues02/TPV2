#pragma once
#include "Component.h"
#include  "Transform.h"
#include "BulletsPool.h"

class Gun : public Component
{
public:
	Gun();
	Gun(SDL_Keycode shoot, BulletsPool* bulletPool);
	void init() override;
	void update() override;
	virtual ~Gun();
private:
	SDL_Keycode shoot;
	Transform* tr_;
	BulletsPool* b_pool;
	Uint32 cd = 0;	//registra la ultima vez que se disparó
	size_t limitTime = 250;//tiempo entre cada dissparo minimo
};

