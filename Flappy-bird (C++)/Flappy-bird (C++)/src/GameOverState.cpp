#include "GameOverState.h"
#include "GameState.h"

namespace Flappy {

	GameOverState::GameOverState(std::shared_ptr<GameData> data, int score) :
		m_data(data)
	{
		m_scoreText.setString(std::to_string(score));
	}

	void GameOverState::init()
	{
		int score = std::stoi(m_scoreText.getString().toWideString(), nullptr, 10);

		m_background.setTexture(m_data->m_assets.getTexture("Game Over Background"));
		m_background.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_gameOverTitle.setTexture(m_data->m_assets.getTexture("Game Over Title"));
		m_gameOverTitle.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_gameOverBody.setTexture(m_data->m_assets.getTexture("Game Over Body"));
		m_gameOverBody.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_retryButton.setTexture(m_data->m_assets.getTexture("Retry Button"));
		m_retryButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		if (m_data->m_sounds) {
			m_soundButton.setTexture(m_data->m_assets.getTexture("Volume on"));
		}
		else {
			m_soundButton.setTexture(m_data->m_assets.getTexture("Volume off"));
		}
		if (m_data->m_effects) {
			m_effectsButton.setTexture(m_data->m_assets.getTexture("Effects on"));
		}
		else {
			m_effectsButton.setTexture(m_data->m_assets.getTexture("Effects off"));
		}
		m_soundButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_effectsButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		if (score >= PLATINUM_MEDAL_SCORE) {
			m_medal.setTexture(m_data->m_assets.getTexture("Platinum Medal"));
		}
		else if (score >= GOLD_MEDAL_SCORE) {
			m_medal.setTexture(m_data->m_assets.getTexture("Gold Medal"));
		}
		else if (score >= SILVER_MEDAL_SCORE) {
			m_medal.setTexture(m_data->m_assets.getTexture("Silver Medal"));
		}
		else if (score >= BRONZE_MEDAL_SCORE) {
			m_medal.setTexture(m_data->m_assets.getTexture("Bronze Medal"));
		}
		m_medal.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		m_gameOverBody.setPosition(static_cast<float>((m_data->m_window.getSize().x / 2) - (m_gameOverBody.getGlobalBounds().width / 2)), 
								   static_cast<float>((m_data->m_window.getSize().y / 2) - (m_gameOverBody.getGlobalBounds().height / 2)));
		m_gameOverTitle.setPosition(static_cast<float>((m_data->m_window.getSize().x / 2) - (m_gameOverTitle.getGlobalBounds().width / 2)),
									static_cast<float>(m_gameOverBody.getPosition().y - (m_gameOverBody.getGlobalBounds().height / 2)));
		m_retryButton.setPosition(static_cast<float>((m_data->m_window.getSize().x / 2) - (m_retryButton.getGlobalBounds().width / 2)),
								  static_cast<float>(m_gameOverBody.getPosition().y + (m_gameOverBody.getGlobalBounds().height / 2) + (m_retryButton.getGlobalBounds().height)));
		m_medal.setPosition(m_gameOverBody.getPosition().x + (m_gameOverBody.getGlobalBounds().width / 8), m_gameOverBody.getPosition().y + (m_gameOverBody.getGlobalBounds().height / 3));
		m_soundButton.setPosition(m_data->m_window.getSize().x - m_soundButton.getGlobalBounds().width - 10,
								  m_data->m_window.getSize().y - m_soundButton.getGlobalBounds().height - 10);
		m_effectsButton.setPosition(m_soundButton.getPosition().x - m_effectsButton.getGlobalBounds().width - 10,
									m_soundButton.getPosition().y);

		m_scoreText.setFont(m_data->m_assets.getFont("Flappy Font"));
		m_scoreText.setCharacterSize(48);
		m_scoreText.setFillColor(sf::Color::White);
		m_scoreText.setOrigin(m_scoreText.getGlobalBounds().width, 0);

		m_highScoreText = m_scoreText;
		
		m_scoreText.setPosition(m_gameOverBody.getPosition().x + m_gameOverBody.getGlobalBounds().width - (m_gameOverBody.getGlobalBounds().width / 10),
								m_gameOverBody.getPosition().y + (m_gameOverBody.getGlobalBounds().height / 2) - m_scoreText.getGlobalBounds().height - (m_gameOverBody.getGlobalBounds().height / 18));
		m_highScoreText.setPosition(m_gameOverBody.getPosition().x + m_gameOverBody.getGlobalBounds().width - (m_gameOverBody.getGlobalBounds().width / 10),
									m_gameOverBody.getPosition().y + (m_gameOverBody.getGlobalBounds().height / 2) + (m_gameOverBody.getGlobalBounds().height / 9));

		std::ifstream file;
		file.open(HIHG_SCORE_FILEPATH);
		int highscore;
		if (file.is_open()) {
			file >> highscore;
		}
		file.close();
		
		if (score > highscore) {
			std::ofstream file;
			file.open(HIHG_SCORE_FILEPATH);
			if (file.is_open())	{
				file << score;
			}
			file.close();
		}
		else {
			m_highScoreText.setString(std::to_string(highscore));
		}
	}

	void GameOverState::handleInput()
	{
		sf::Event event;

		while (m_data->m_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				m_data->m_window.close();
			}
			else if (m_data->m_input.isSpriteClicked(m_retryButton, sf::Mouse::Left, m_data->m_window)) {
				m_data->m_machine.addState(std::unique_ptr<State>(new GameState(m_data)), true);
			}
			else if (m_data->m_input.isSpriteClicked(m_soundButton, sf::Mouse::Left, m_data->m_window)) {
				if (m_data->m_sounds) {
					m_soundButton.setTexture(m_data->m_assets.getTexture("Volume off"));
					m_data->m_sounds = false;
				}
				else {
					m_soundButton.setTexture(m_data->m_assets.getTexture("Volume on"));
					m_data->m_sounds = true;
				}
			}
			else if (m_data->m_input.isSpriteClicked(m_effectsButton, sf::Mouse::Left, m_data->m_window)) {
				if (m_data->m_effects) {
					m_effectsButton.setTexture(m_data->m_assets.getTexture("Effects off"));
					m_data->m_effects = false;
				}
				else {
					m_effectsButton.setTexture(m_data->m_assets.getTexture("Effects on"));
					m_data->m_effects = true;
				}
			}
		}
	}

	void GameOverState::update(float dt)
	{
	}

	void GameOverState::draw(float dt)
	{
		m_data->m_window.clear();
		m_data->m_window.draw(m_background);
		m_data->m_window.draw(m_gameOverTitle);
		m_data->m_window.draw(m_gameOverBody);
		m_data->m_window.draw(m_retryButton);
		m_data->m_window.draw(m_scoreText);
		m_data->m_window.draw(m_highScoreText);
		m_data->m_window.draw(m_medal);
		m_data->m_window.draw(m_effectsButton);
		m_data->m_window.draw(m_soundButton);
		m_data->m_window.display();
	}
}