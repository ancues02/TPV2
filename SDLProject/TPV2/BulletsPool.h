#pragma once
#include "Component.h"
#include "ObjectPool.h"
//#include "AsteroidPool.h"
class BulletsPool : public Component
{
public:
	struct Bullet {
		Vector2D pos_, vel;
		int rotation;
		int width_;
		int height_;
		bool inUse = false;
	};
	BulletsPool();
	virtual ~BulletsPool();



	void init() override;
	//void update() override;
	void shoot(Vector2D pos, Vector2D vel, double w, double h);
	void disableAll();
	//void onCollision(Bullet* a, AsteroidPool::Asteroid* b);
	//size_t getNumOfAsteroid();
	std::vector<Bullet*> getPool();
private:
	ObjectPool<Bullet, 10> pool;
};


