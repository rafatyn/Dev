#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include <fstream>
#include <string>

namespace Flappy {

	class GameOverState : public State
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Sprite m_background;
		sf::Sprite m_gameOverTitle;
		sf::Sprite m_gameOverBody;
		sf::Sprite m_retryButton;
		sf::Sprite m_medal;
		sf::Sprite m_soundButton;
		sf::Sprite m_effectsButton;

		sf::Text m_scoreText;
		sf::Text m_highScoreText;
	public:
		GameOverState(std::shared_ptr<GameData> data, int score);

		void init() override;

		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;
	};
}