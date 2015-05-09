#include <iostream>

#include "SFML\Graphics.hpp"
#include "Game.h"
#include "GFramework.h"

int main()
{
	srand(time(NULL));

	Gf::window = new sf::RenderWindow;
	Gf::window->create(sf::VideoMode(800, 600), "Game");

	Gf::game = new Game;

	// initialize game
	Gf::game->Initialize();

	while (Gf::window->isOpen())
	{
		// update game
		Gf::game->Update(0.0f);

		sf::Event event;
		while (Gf::window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				Gf::window->close();
				break;
			}
		}

		Gf::window->clear(sf::Color(100.0f, 100.0f, 100.0f));
		Gf::game->Draw();
		Gf::window->display();
	}

	Gf::game->release();
	delete Gf::window;

	return 0;
}