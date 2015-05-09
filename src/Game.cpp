#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

/*
void Game::Initialize()
{
	world.CollisionCallback = [&](GameObject* A, GameObject* B) {
		
	};

	player.Load("data/gfx/player_bloom.png");
	player.Rotated = 90.0f;
	player.Position = Gf::Vector2(300.0f, 100.0f);
	player.Scale = 0.5f;
//	player.MakeHalfTransparent(true);
	player.MakeOriginCenter();

	grass.Load("data/gfx/grass_bloom.png");

	z.Create();

	z2.Create();
	z2.Teleport(Gf::Vector2(20.0f, 400.0f));
	
	zombieAnim.AddFrames("data/gfx/", "zombie", 2);

	policeCar.Load("data/gfx/Police_animation/police0.png");
	policeCar.Position.X = 600.0f;
	policeCar.Position.Y = 200.0f;
	policeCar.Rotation = 20.0f;
	policeCar.MakeOriginCenter(true);

	sirensOnAnim.AddFrames("data/gfx/Police_animation/", "police", 3);

	policeCarAnimSet.Add("sirens_on", sirensOnAnim);
	policeCarAnimSet.SetSprite(&policeCar);



	policeCarAnimSet.PlayedAnimation = "sirens_on";

	
}

void Game::Update(float dt)
{
	//zombieAnim.Play(&player, 2.0f);
	sirensOnAnim.Play(&policeCar, 0.1f);

	player.Rotation += 0.02f;
	z.Update(dt);
	z2.Update(dt);

	//policeCarAnimSet.Play();
}

void Game::Draw()
{
	grass.DrawTiled(10, 10);
	player.Draw();
	z.Draw();
	z2.Draw();
	policeCar.Draw();
}*/

#include "Box.h"

void Game::Initialize()
{
	bg.Load("data/dev/bg.png");

	
	Box* boxA = new Box;
	boxA->Moving = true;
	boxA->Create();

	Box* boxB = new Box;
	boxB->Moving = false;
	boxB->Create();

	Box* boxC = new Box;
	boxC->Moving = false;
	boxC->Create();

	Zombie * z = new Zombie;
	z->Create();

	Gf::game->store<Box>(boxA, "boxA");
	Gf::game->store<Box>(boxB, "boxB");
	Gf::game->store<Zombie>(z, "boxC");

	boxC->Teleport(Gf::Vector2(10.0f, 100.0f));
	boxA->Teleport(Gf::Vector2(200.0f, 100.0f));
	boxB->Teleport(Gf::Vector2(500.0f, 100.0f));

	world.Add(boxA);
	world.Add(boxB);
	world.Add(boxC);
}

void Game::Draw()
{
	bg.DrawTiled(20, 20);

	Gf::game->get<Box>("boxA")->Draw();
	Gf::game->get<Box>("boxB")->Draw();
	Gf::game->get<Box>("boxC")->Draw();
}

void Game::Update(float dt)
{
	world.Update();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Gf::game->get<Box>("boxA")->Velocity.X = 0.1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Gf::game->get<Box>("boxA")->Velocity.X = -0.1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Gf::game->get<Box>("boxA")->Velocity.Y = -0.1f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Gf::game->get<Box>("boxA")->Velocity.Y = 0.1f;
	}
	else
	{
		Gf::game->get<Box>("boxA")->Velocity.X = 0.0f;
		Gf::game->get<Box>("boxA")->Velocity.Y = 0.0f;
	}

	Gf::game->get<Box>("boxA")->Update(dt);
	Gf::game->get<Box>("boxB")->Update(dt);
	Gf::game->get<Box>("boxC")->Update(dt);
}