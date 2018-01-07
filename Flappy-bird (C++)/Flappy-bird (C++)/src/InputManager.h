#pragma once

#include <SFML/Graphics.hpp>

namespace Flappy {
	
	class InputManager
	{
	public:
		InputManager() {}
		~InputManager() {}

		bool isSpriteClicked(sf::Sprite& sprite, sf::Mouse::Button button, sf::RenderWindow& window);

		sf::Vector2i getMousePosition(sf::RenderWindow& window);
	};
}