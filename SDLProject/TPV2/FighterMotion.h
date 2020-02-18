#pragma once
#include "Component.h"
#include "Transform.h"

class FighterMotion:public Component
{
public:
	FighterMotion();
	virtual ~FighterMotion();
	void init() override;
	void update() override;
private:
	Transform* tr_;
};

