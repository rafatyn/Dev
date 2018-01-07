#pragma once

#include <SFML/Graphics.hpp>

namespace Flappy {

	class Colision
	{
	public:
		static bool checkColision(sf::Sprite sprite1, sf::Sprite sprite2);
		static bool checkColision(sf::Sprite sprite1, float scale1, float scale2, sf::Sprite sprite2);
	};
}