#pragma once

#include "GFramework.h"



class Box : public Gf::GameObject
{
public:
	Box();
	~Box();



	void Create()
	{
		sprite.Load("data/dev/33.png");
		
		Size = Gf::Vector2(static_cast<float>(sprite.GetWidth()),
							static_cast<float>(sprite.GetHeight()));

		Position = Gf::Vector2(20.0f, 20.0f);
		

		if (Moving)
		{
			//Velocity.X = 0.04f;
		}
		else
		{
			//Velocity.X = 0.0f;
		}

	}

	void Update(float dt)
	{
		

		UpdatePosition();
	
	}

	void Draw()
	{
		DrawSprite(&sprite);
	//	sprite.Draw();
	}

	bool Moving;

private:
	Gf::Sprite sprite;
};

