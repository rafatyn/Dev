#include "Land.h"
 
namespace Flappy {

	Land::Land(std::shared_ptr<GameData> data) :
		m_data(data)
	{
		sf::Sprite sprite(m_data->m_assets.getTexture("Land"));
		sf::Sprite sprite2(m_data->m_assets.getTexture("Land"));

		sprite.setScale(DEFAULT_SCREEN_WIDTH / (sprite.getGlobalBounds().width-1), SCREEN_SCALE_HEIGHT);
		sprite.setPosition(0, m_data->m_window.getSize().y - sprite.getGlobalBounds().height);

		sprite2.setScale(DEFAULT_SCREEN_WIDTH / (sprite2.getGlobalBounds().width-1), SCREEN_SCALE_HEIGHT);
		sprite2.setPosition(sprite.getGlobalBounds().width, m_data->m_window.getSize().y - sprite2.getGlobalBounds().height);

		m_lands.push_back(sprite);
		m_lands.push_back(sprite2);
	}

	void Land::moveLand(float dt)
	{
		float movement = PIPE_MOVEMENT_SPEED * dt;
		for (unsigned int i = 0; i < m_lands.size(); i++) {
			m_lands[i].move(-movement, 0);
			if (m_lands[i].getPosition().x < 0 - m_lands[i].getGlobalBounds().width) {
				m_lands[i].setPosition(sf::Vector2f(static_cast<float>(m_data->m_window.getSize().x), m_lands[i].getPosition().y));
				m_lands.push_back(m_lands[i]);
				m_lands.erase(m_lands.begin());
				i--;
			}
		}
	}

	void Land::drawLand()
	{
		for (const auto & land : m_lands) {
			m_data->m_window.draw(land);
		}
	}

	const std::vector<sf::Sprite>& Land::getSprite() const
	{
		return m_lands;
	}

}