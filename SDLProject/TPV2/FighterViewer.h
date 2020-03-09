#pragma once

#include "Component.h"
#include "Transform.h"

class FighterViewer:public Component{
public:
	FighterViewer();
	virtual ~FighterViewer();
	void init() override;
	void draw() override;
private:
	Transform* tr_;
	Texture* texture=nullptr;
};