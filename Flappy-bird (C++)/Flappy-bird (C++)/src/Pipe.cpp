#include "Pipe.h"

namespace Flappy {

	Pipe::Pipe(std::shared_ptr<GameData> data) :
		m_data(data)
	{
		sf::Sprite sprite(data->m_assets.getTexture("Land"));
		sprite.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		m_landHeight = static_cast<int>(sprite.getGlobalBounds().height);
		m_pipeYOffset = 0;
		srand(static_cast<unsigned int>(time(nullptr)));
	}

	void Pipe::spawnBottomPipe()
	{
		sf::Sprite sprite(m_data->m_assets.getTexture("Pipe Up"));
		sprite.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		sprite.setPosition(static_cast<float>(m_data->m_window.getSize().x), m_data->m_window.getSize().y - sprite.getGlobalBounds().height - m_pipeYOffset);
		m_pipeSprites.push_back(sprite);
	}

	void Pipe::spawnTopPipe()
	{
		sf::Sprite sprite(m_data->m_assets.getTexture("Pipe Down"));
		sprite.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		sprite.setPosition(static_cast<float>(m_data->m_window.getSize().x), static_cast<float>(-m_pipeYOffset));
		m_pipeSprites.push_back(sprite);
	}

	void Pipe::spawnScoringPipe()
	{
		sf::Sprite sprite(m_data->m_assets.getTexture("Scoring Pipe"));
		sf::Sprite pipe(m_data->m_assets.getTexture("Pipe Up"));
		sf::Sprite bird(m_data->m_assets.getTexture("Bird Frame 1"));
		
		sprite.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		pipe.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		bird.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);
		sprite.setPosition(static_cast<float>(m_data->m_window.getSize().x + pipe.getGlobalBounds().width + bird.getGlobalBounds().width), 0);
		m_pipeScoringSprites.push_back(sprite);
	}
	
	void Pipe::movePipes(float dt)
	{
		float movement = PIPE_MOVEMENT_SPEED * dt;
		for (size_t i = 0; i < m_pipeSprites.size(); i++) {
			if (m_pipeSprites[i].getPosition().x < -m_pipeSprites[i].getGlobalBounds().width) {
				m_pipeSprites.erase(m_pipeSprites.begin() + i);
				i--;
			}
			else {
				m_pipeSprites[i].move(-movement, 0);
			}
		}
		for (size_t i = 0; i < m_pipeScoringSprites.size(); i++) {
			if (m_pipeScoringSprites[i].getPosition().x < -m_pipeScoringSprites[i].getGlobalBounds().width) {
				m_pipeScoringSprites.erase(m_pipeScoringSprites.begin() + i);
				i--;
			}
			else {
				m_pipeScoringSprites[i].move(-movement, 0);
			}
		}
	}

	void Pipe::randomizePipeOffset()
	{		
		m_pipeYOffset = rand() % (m_landHeight + 1);
	}

	const std::vector<sf::Sprite> & Pipe::getSprites() const
	{
		return m_pipeSprites;
	}

	std::vector<sf::Sprite> & Pipe::getScoringSprites()
	{
		return m_pipeScoringSprites;
	}

	void Pipe::drawPipes()
	{
		for (const auto & pipeSprite : m_pipeSprites) {
			m_data->m_window.draw(pipeSprite);
		}
	}
}