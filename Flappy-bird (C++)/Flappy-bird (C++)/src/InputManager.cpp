#include "InputManager.h"

namespace Flappy {

	bool InputManager::isSpriteClicked(sf::Sprite & sprite, sf::Mouse::Button button, sf::RenderWindow & window)
	{
		if (sf::Mouse::isButtonPressed(button))	{
			sf::IntRect spriteArea(static_cast<int>(sprite.getPosition().x), static_cast<int>(sprite.getPosition().y),
								   static_cast<int>(sprite.getGlobalBounds().width), static_cast<int>(sprite.getGlobalBounds().height));

			if (spriteArea.contains(sf::Mouse::getPosition(window))) {
				return true;
			}
		}
		return false;
	}
	sf::Vector2i InputManager::getMousePosition(sf::RenderWindow & window)
	{
		return sf::Mouse::getPosition(window);
	}
}