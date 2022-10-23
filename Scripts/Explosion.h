#pragma once
#include "Entity.h"
class Explosion : public Entity
{
private:
	float helpTime;
	int textureX;
public:
	Explosion();
	void update();
};

