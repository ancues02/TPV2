#pragma once
#include "Component.h"
#include "Texture.h"
#include "BulletsPool.h"
class BulletsViewer : public Component
{
public:
	BulletsViewer();
	virtual ~BulletsViewer();
	void init() override;
	void draw() override;
private:
	BulletsPool* pool;
	Texture* texture = nullptr;
};

