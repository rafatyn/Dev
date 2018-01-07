#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

namespace Flappy {

	class Bird 
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Sprite m_birdSprite;
		std::vector<sf::Texture> m_animationFrames;
		unsigned int m_animationIterator;
		sf::Clock m_clock;
		sf::Clock m_movementClock;
		int m_birdState;
		float m_rotation;
	public:
		Bird(std::shared_ptr<GameData> data);

		void draw();
		void animate(float dt);
		void update(float dt);
		void tap();

		const sf::Sprite& getSprite() const;
	};
}