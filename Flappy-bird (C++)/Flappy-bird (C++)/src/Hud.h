#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Flappy {

	class Hud 
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Text m_text;
		sf::Text m_textShadow;
	public:
		Hud(std::shared_ptr<GameData> data);

		void draw();
		void update(int score);
	};
}