#pragma once

#include "State.h"
#include "Game.h"

namespace Flappy {

	class MainMenuState : public State
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Sprite m_background;
		sf::Sprite m_title;
		sf::Sprite m_playButton;
		sf::Sprite m_soundButton;
		sf::Sprite m_effectsButton;
	public:
		MainMenuState(std::shared_ptr<GameData> data);

		void init() override;

		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;
	};
}