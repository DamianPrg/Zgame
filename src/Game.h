#pragma once

#include "SFML\Graphics.hpp"
#include "GFramework.h"
#include "Zombie.h"
#include "World.h"

class GameObject;

class Game : public Gf::IGame
{
public:
	Game();
	~Game();

	void Initialize();
	void Update(float dt);
	void Draw();

private:
	Gf::Sprite player;
	Zombie z;
	Gf::Sprite grass;
	Zombie z2;

	Gf::Animation zombieAnim;

	Gf::Sprite policeCar;
	Gf::Animation sirensOnAnim;
	Gf::AnimationSet policeCarAnimSet;

	
	World world;

	Gf::Sprite bg;
};

