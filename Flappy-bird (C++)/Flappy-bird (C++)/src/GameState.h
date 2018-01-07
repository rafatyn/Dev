#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Flash.h"
#include "Colision.h"
#include "Hud.h"

namespace Flappy {

	class GameState : public State
	{
	private:
		std::shared_ptr<GameData> m_data;
		sf::Sprite m_background;
		Pipe *m_pipes;
		Land *m_lands;
		Bird *m_bird;
		Flash *m_flash;
		Hud *m_hud;
		sf::Clock m_clock;
		GameStates m_gameState;
		int m_score;
		sf::Sound m_hitSound;
		sf::Sound m_pointSound;
		sf::Sound m_wingSound;
		sf::Sound m_ambientSound;
	public:
		GameState(std::shared_ptr<GameData> data);
		~GameState();

		void init() override;

		void handleInput() override;
		void update(float dt) override;
		void draw(float dt) override;
	};
}