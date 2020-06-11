#pragma once
#include "System.h"
class AudioSystem : public System
{
public:

	AudioSystem();

	void init() override;
	void recieve(const msg::Message& msg) override;
};

