#pragma once
#include "Component.h"
#include "ObjectPool.h"

class Asteroid;
struct Bullet {
public:
	Vector2D pos_, vel;
	int rotation;
	int width_;
	int height_;
	bool inUse = false;
};

class BulletsPool : public Component
{
public:
	BulletsPool();
	virtual ~BulletsPool();
	void init() override;
	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();
	void onCollision(Bullet* a, Asteroid* b);
	std::vector<Bullet*> getPool();
private:
	ObjectPool<Bullet, 10> pool;
};


