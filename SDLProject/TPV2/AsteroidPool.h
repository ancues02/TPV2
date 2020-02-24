#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Asteroid.h"
#include "SRandBasedGenerator.h"
class AsteroidPool : public Component
{
public:
	AsteroidPool();
	virtual ~AsteroidPool();

	

	void init() override;
	void update() override;
	void generateAsteroids(int n);
private:
	//ObjectPool<Asteroid,30> pool;
};

