#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Flappy {

	class Flash
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::RectangleShape m_shape;
		bool m_flashOn;
	public:
		Flash(std::shared_ptr<GameData> data);

		void turnOn();
		void show(float dt);
		void draw();
	};
}