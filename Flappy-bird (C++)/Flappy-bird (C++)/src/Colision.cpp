#include "Colision.h"

namespace Flappy {

	bool Colision::checkColision(sf::Sprite sprite1, sf::Sprite sprite2)
	{
		if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {
			return true;
		}
		return false;
	}

	bool Colision::checkColision(sf::Sprite sprite1, float scale1, float scale2, sf::Sprite sprite2)
	{
		sprite1.setScale(sprite1.getScale().x*scale1, sprite1.getScale().y*scale2);

		if (sprite1.getGlobalBounds().intersects(sprite2.getGlobalBounds())) {
			return true;
		}
		return false;
	}

}