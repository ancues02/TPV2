#pragma once
#include "Component.h"
#include  "Transform.h"
class Health : public Component
{
public:
	Health();
	virtual ~Health();
	void init() override;
	void draw() override;
	void decrease_health(int damage = 1);
	void reset_health();
	int getHealth() {
		return health;
	}
private:
	Transform* tr_;
	Texture* texture = nullptr;
	int health, 
		ini_health = 3;

};

