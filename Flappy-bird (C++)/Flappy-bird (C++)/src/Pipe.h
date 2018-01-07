#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

namespace Flappy {

	class Pipe 
	{
	private:
		std::shared_ptr<GameData> m_data;
		std::vector<sf::Sprite> m_pipeSprites;
		std::vector<sf::Sprite> m_pipeScoringSprites;

		int m_landHeight;
		int m_pipeYOffset;
	public:
		Pipe(std::shared_ptr<GameData> data);

		void drawPipes();

		void spawnBottomPipe();
		void spawnTopPipe();
		void spawnScoringPipe();
		void movePipes(float dt);
		void randomizePipeOffset();

		const std::vector<sf::Sprite> &getSprites() const;
		std::vector<sf::Sprite> &getScoringSprites();
	};
}