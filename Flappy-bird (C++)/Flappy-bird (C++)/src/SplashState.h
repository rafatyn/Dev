#pragma once

#include <thread>
#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace Flappy {

	class SplashState : public State
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Clock m_clock;
		sf::Sprite m_background;
		std::thread loadThread;
	public:
		SplashState(std::shared_ptr<GameData> data);

		void init() override;

		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;		

		void loadAssets();
	};
}