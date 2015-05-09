#pragma once

#include "GFramework.h"

class Zombie : public Gf::GameObject
{
public:
	Zombie();
	~Zombie();

	void Create();
	void Update(float dt);
	void Draw();

private:
	Gf::Sprite zombie;
};

