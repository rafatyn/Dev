#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.h"
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace Flappy {

	struct GameData
	{
		StateMachine m_machine;
		sf::RenderWindow m_window;
		AssetManager m_assets;
		InputManager m_input;
		bool m_effects, m_sounds;
	};

	class Game
	{
	private:
		std::shared_ptr<GameData> m_data = std::make_shared<GameData>();
	public:
		Game(int width, int height, const char* name);
		Game(float width, float height, const char* name);
		~Game() = default;
	
		void run();
	};
}