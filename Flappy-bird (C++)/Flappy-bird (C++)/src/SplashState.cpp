#include "SplashState.h"
#include "MainMenuState.h"

namespace Flappy {
	
	SplashState::SplashState(std::shared_ptr<GameData> data) :
		m_data(data)
	{}

	void SplashState::init()
	{
		m_data->m_assets.addTexture("Splash Background", SPLASH_PATH);

		m_background.setTexture(m_data->m_assets.getTexture("Splash Background"));
		m_background.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		loadThread = std::thread(&SplashState::loadAssets, this);
	}

	void SplashState::handleInput()
	{
		sf::Event event;

		while (m_data->m_window.pollEvent(event)) {
			if (sf::Event::Closed == event.type) {
				m_data->m_window.close();
			}
		}
	}

	void SplashState::update(float dt)
	{
		if (m_clock.getElapsedTime().asSeconds() >= SPLASH_SHOW_TIME) {
			loadThread.join();
			m_data->m_machine.addState(std::unique_ptr<State>(new MainMenuState(m_data)), true);
		}
	}

	void SplashState::draw(float dt)
	{
		m_data->m_window.clear();
		m_data->m_window.draw(m_background);
		m_data->m_window.display();
	}

	void SplashState::loadAssets()
	{
		m_data->m_assets.addTexture("Main Menu Background", MAIN_MENU_PATH);
		m_data->m_assets.addTexture("Game Title", GAME_TITLE_FILEPATH);
		m_data->m_assets.addTexture("Play Button", PLAY_BUTTON_FILEPATH);
		m_data->m_assets.addTexture("Volume on", VOLUME_ON_FILEPATH);
		m_data->m_assets.addTexture("Volume off", VOLUME_OFF_FILEPATH);
		m_data->m_assets.addTexture("Effects on", EFFECTS_ON_FILEPATH);
		m_data->m_assets.addTexture("Effects off", EFFECTS_OFF_FILEPATH);
		m_data->m_assets.addTexture("Game Background", GAME_BACKGROUND_PATH);
		m_data->m_assets.addTexture("Pipe Up", PIPE_UP_FILEPATH);
		m_data->m_assets.addTexture("Pipe Down", PIPE_DOWN_FILEPATH);
		m_data->m_assets.addTexture("Scoring Pipe", PIPE_SCORING_FILEPATH);
		m_data->m_assets.addTexture("Land", LAND_FILEPATH);
		m_data->m_assets.addTexture("Bird Frame 1", BIRD_FRAME1_FILEPATH);
		m_data->m_assets.addTexture("Bird Frame 2", BIRD_FRAME2_FILEPATH);
		m_data->m_assets.addTexture("Bird Frame 3", BIRD_FRAME3_FILEPATH);
		m_data->m_assets.addTexture("Bird Frame 4", BIRD_FRAME4_FILEPATH);
		m_data->m_assets.addTexture("Game Over Background", GAME_OVER_BACKGROUND_PATH);
		m_data->m_assets.addTexture("Game Over Title", GAME_OVER_TITLE_FILEPATH);
		m_data->m_assets.addTexture("Game Over Body", GAME_OVER_BODY_FILEPATH);
		m_data->m_assets.addTexture("Retry Button", PLAY_BUTTON_FILEPATH);
		m_data->m_assets.addTexture("Bronze Medal", BRONZE_GAME_OVER_MEDAL);
		m_data->m_assets.addTexture("Silver Medal", SILVER_GAME_OVER_MEDAL);
		m_data->m_assets.addTexture("Gold Medal", GOLD_GAME_OVER_MEDAL);
		m_data->m_assets.addTexture("Platinum Medal", PLATINUM_GAME_OVER_MEDAL);
		m_data->m_assets.addFont("Flappy Font", FLAPPY_FONT_FILEPATH);
		m_data->m_assets.addSound("Hit", HIT_SOUND_FILEPATH);
		m_data->m_assets.addSound("Wing", WING_SOUND_FILEPATH);
		m_data->m_assets.addSound("Point", POINT_SOUND_FILEPATH);
		m_data->m_assets.addSound("Ambient", AMBIENT_SOUND_FILEPATH);
	}
}