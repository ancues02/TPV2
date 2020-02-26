#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "BulletsPool.h"
class AsteroidPool : public Component
{
public:
	struct Asteroid {
		Vector2D pos_,vel;
		int rotation;
		int width_;
		int height_;
		int gen;
		bool inUse = false;
	};
	AsteroidPool();
	virtual ~AsteroidPool();

	

	void init() override;
	//void update() override;
	void generateAsteroids(int n);
	void disableAll();
	void onCollision(Asteroid* a, BulletsPool::Bullet* b);
	size_t getNumOfAsteroid();
	std::vector<Asteroid*> getPool();
private:

	ObjectPool<Asteroid,30> pool;
};

