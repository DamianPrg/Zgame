#include "Zombie.h"


Zombie::Zombie()
{
}


Zombie::~Zombie()
{
}

void Zombie::Create()
{
	Gf::Log("Zombie", "Create");

	zombie.Load("data/gfx/zombie_bloom.png");
	zombie.Rotated = 90.0f;
	zombie.Scale = 0.5f;

	zombie.Position = Gf::Vector2(10.0f, 300.0f);
	this->Position = Gf::Vector2(10.0f, 300.0f);

	zombie.MakeOriginCenter(true);
	//zombie.MakeHalfTransparent(true);
}

void Zombie::Update(float dt)
{
	zombie.Position = this->Position;
	//zombie.Position.X += 0.1f*sin(zombie.Rotation);
	//zombie.Rotation -= 0.01f;

//	this->Position.X += 0.01f;
}

void Zombie::Draw()
{
	zombie.Draw();
}