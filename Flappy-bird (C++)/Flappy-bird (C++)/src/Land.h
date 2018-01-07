#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace Flappy {

	class Land 
	{
	private:
		std::shared_ptr<GameData> m_data;
		std::vector<sf::Sprite> m_lands;
	public:
		Land(std::shared_ptr<GameData> data);
		
		void moveLand(float dt);
		void drawLand();

		const std::vector<sf::Sprite>& getSprite() const;
	};
}