#include "GameState.h"
#include "GameOverState.h"

namespace Flappy {

	GameState::GameState(std::shared_ptr<GameData> data) :
		m_data(data)
	{}

	GameState::~GameState()
	{
		delete m_pipes;
		delete m_lands;
		delete m_bird;
		delete m_flash;
		delete m_hud;
	}

	void GameState::init()
	{
		m_pipes = new Pipe(m_data);
		m_lands = new Land(m_data);
		m_bird = new Bird(m_data);
		m_flash = new Flash(m_data);
		m_hud = new Hud(m_data);

		m_background.setTexture(m_data->m_assets.getTexture("Game Background"));
		m_background.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		m_hitSound.setBuffer(m_data->m_assets.getSound("Hit"));
		m_pointSound.setBuffer(m_data->m_assets.getSound("Point"));
		m_wingSound.setBuffer(m_data->m_assets.getSound("Wing"));
		m_ambientSound.setBuffer(m_data->m_assets.getSound("Ambient"));

		if (m_data->m_sounds) {
			m_ambientSound.setLoop(true);
			m_ambientSound.setVolume(50);
			m_ambientSound.play();
		}

		m_gameState = GameStates::eReady;
		m_score = 0;
	}

	void GameState::handleInput()
	{
		sf::Event event;

		while (m_data->m_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				m_data->m_window.close();
			}
			if (m_data->m_input.isSpriteClicked(m_background, sf::Mouse::Left, m_data->m_window)) {
				if (m_gameState != GameStates::eGameOver) {
					m_gameState = GameStates::ePlaying;
					m_bird->tap();
					if (m_data->m_effects) {
						m_wingSound.play();
					}
				}
			}
		}
	}

	void GameState::update(float dt)
	{
		if (m_gameState != GameStates::eGameOver) {
			m_bird->animate(dt);
			m_lands->moveLand(dt);
		}

		if(m_gameState == GameStates::ePlaying) {
			m_pipes->movePipes(dt);
			if (m_clock.getElapsedTime().asSeconds() >= PIPE_SPAWN_FRECUENCY) {
				m_pipes->randomizePipeOffset();
				m_pipes->spawnBottomPipe();
				m_pipes->spawnScoringPipe();
				m_pipes->spawnTopPipe();
				m_clock.restart();
			}
			m_bird->update(dt);

			std::vector<sf::Sprite> lands = m_lands->getSprite();

			for (const auto& land : lands) {
				if (Colision::checkColision(m_bird->getSprite(), land)) {
					m_gameState = GameStates::eGameOver;
					m_flash->turnOn();
					m_clock.restart();
					if (m_data->m_effects) {
						m_hitSound.play();
					}
				}
			}

			std::vector<sf::Sprite> pipes = m_pipes->getSprites();

			for (auto &pipe : pipes) {
				if (Colision::checkColision(m_bird->getSprite(), 0.65f, 0.9f, pipe)) {
					m_gameState = GameStates::eGameOver;
					m_flash->turnOn();
					m_clock.restart();
					if (m_data->m_effects) {
						m_hitSound.play();
					}
				}
			}

			std::vector<sf::Sprite> &scoringPipes = m_pipes->getScoringSprites();

			for (const auto & scoringPipe : scoringPipes) {
				if (Colision::checkColision(m_bird->getSprite(), 0.65f, 0.9f, scoringPipe)) {
					m_score++;
					scoringPipes.erase(scoringPipes.begin());
					m_hud->update(m_score);
					if (m_data->m_effects) {
						m_pointSound.play();
					}
				}
			}
		}

		if (m_gameState == GameStates::eGameOver) {
			m_flash->show(dt);
			if (m_clock.getElapsedTime().asSeconds() >= TIME_BEFORE_GAME_OVER) {
				m_ambientSound.stop();
				m_data->m_machine.addState(std::unique_ptr<State>(new GameOverState(m_data, m_score)), true);
			}
		}
	}

	void GameState::draw(float dt)
	{
		m_data->m_window.clear();
		m_data->m_window.draw(m_background);
		m_pipes->drawPipes();
		m_lands->drawLand();
		m_bird->draw();
		m_flash->draw();
		m_hud->draw();
		m_data->m_window.display();
	}
}