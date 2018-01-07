#include "Game.h"
#include "SplashState.h"
#include <cstdlib>

namespace Flappy {
	
	Game::Game(int width, int height, const char* name)
	{
		m_data->m_window.create(sf::VideoMode(width, height), name, sf::Style::Close | sf::Style::Titlebar);
		m_data->m_machine.addState(std::unique_ptr<State>(new SplashState(m_data)), false);
		m_data->m_effects = true;
		m_data->m_sounds = true;

		run();
	}

	Game::Game(float width, float height, const char* name)
	{
		m_data->m_window.create(sf::VideoMode(static_cast<unsigned int>(width), static_cast<unsigned int>(height)),
							    name, sf::Style::Close | sf::Style::Titlebar);
		m_data->m_machine.addState(std::unique_ptr<State>(new SplashState(m_data)), false);
		m_data->m_effects = true;
		m_data->m_sounds = true;

		run();
	}

	void Game::run()
	{
		float updateTick = 1.0f / 60.0f;

		sf::Clock time;
		while (m_data->m_window.isOpen()) {			
			m_data->m_machine.processStateChanges();
			if (time.getElapsedTime().asSeconds() >= updateTick) {
				m_data->m_machine.getActiveState()->handleInput();
				m_data->m_machine.getActiveState()->update(time.getElapsedTime().asSeconds());
				time.restart();
			}
			m_data->m_machine.getActiveState()->draw(updateTick);
		}
	}
}