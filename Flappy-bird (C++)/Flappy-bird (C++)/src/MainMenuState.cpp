#include "MainMenuState.h"
#include "GameState.h"

namespace Flappy {
	
	MainMenuState::MainMenuState(std::shared_ptr<GameData> data) :
		m_data(data)
	{}

	void MainMenuState::init()
	{
		m_background.setTexture(m_data->m_assets.getTexture("Main Menu Background"));
		m_title.setTexture(m_data->m_assets.getTexture("Game Title"));
		m_playButton.setTexture(m_data->m_assets.getTexture("Play Button"));
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

		m_background.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_title.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_playButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_soundButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_effectsButton.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		m_title.setPosition((m_data->m_window.getSize().x / 2) - (m_title.getGlobalBounds().width / 2),
							m_title.getGlobalBounds().height / 2);
		m_playButton.setPosition((m_data->m_window.getSize().x / 2) - (m_playButton.getGlobalBounds().width / 2),
								 (m_data->m_window.getSize().y / 2) - (m_playButton.getGlobalBounds().height / 2));
		m_soundButton.setPosition(m_data->m_window.getSize().x - m_soundButton.getGlobalBounds().width - 10,
								  m_data->m_window.getSize().y - m_soundButton.getGlobalBounds().height - 10);
		m_effectsButton.setPosition(m_soundButton.getPosition().x - m_effectsButton.getGlobalBounds().width - 10, 
									m_soundButton.getPosition().y);
	}
	
	void MainMenuState::handleInput()
	{
		sf::Event event;

		while (m_data->m_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				m_data->m_window.close();
			}
			else if (m_data->m_input.isSpriteClicked(m_playButton, sf::Mouse::Left, m_data->m_window)) {
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
	
	void MainMenuState::update(float dt) {}
	
	void MainMenuState::draw(float dt)
	{
		m_data->m_window.clear();

		m_data->m_window.draw(m_background);
		m_data->m_window.draw(m_title);
		m_data->m_window.draw(m_playButton);
		m_data->m_window.draw(m_soundButton);
		m_data->m_window.draw(m_effectsButton);

		m_data->m_window.display();
	}
}