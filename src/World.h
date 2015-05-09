#pragma once

#include <vector>
#include <functional>

#include "GFramework.h"
/**
  * Simple physical world.
  *
  */
class World
{
public:
	World();
	~World();

	void Add(Gf::GameObject* obj, bool is_static = false)
	{
		if (obj)
		{
			objects.push_back(obj);
		}
	}

	

	void Update()
	{
		for (int i = 0; i < objects.size(); i++)
		{
			for (int j = 0; j < objects.size(); j++)
			{
				// dont check collision with myself :D
				if (objects[i] != objects[j])
				{
					if (objects[i]->Touches(objects[j]))
					{
						std::cout << "Kolizja: " << i << " , " << j << std::endl;
						
						Gf::GameObject* Collider = objects[j];
						Gf::GameObject* A = objects[i];
						//Collider->Teleport(Gf::Vector2(0.0f, 0.0f));
						//Collider->Velocity.X = -Collider->Velocity.X;
						Collider->Position.X -= Collider->Velocity.X;
						Collider->Velocity.X = 0.0f;
						
						A->Position.X -= A->Velocity.X;
						A->Velocity.X = 0.0f;
						
					}
				}
			}
		}
	}

public:
	std::vector<Gf::GameObject*> objects;
};

