#pragma once
#include "Component.h"
#include "Texture.h"
#include "AsteroidPool.h"
class AsteroidsViewer : public Component
{
public:
	AsteroidsViewer();
	virtual ~AsteroidsViewer();
	void init() override;
	void draw() override;
private:
	AsteroidPool* pool;
	Texture* texture = nullptr;
};

