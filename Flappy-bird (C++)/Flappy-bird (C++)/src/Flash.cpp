#include "Flash.h"

namespace Flappy {

	Flash::Flash(std::shared_ptr<GameData> data) :
		m_data(data)
	{
		m_shape = sf::RectangleShape(sf::Vector2f(data->m_window.getSize()));
		m_shape.setFillColor(sf::Color(255,255,255,0));

		m_flashOn = false;
	}

	void Flash::turnOn()
	{
		m_flashOn = true;
	}

	void Flash::show(float dt)
	{
		if (m_flashOn) {
			float alpha = static_cast<float>(m_shape.getFillColor().a) + (FLASH_SPEED * dt);
			if (alpha >= 255.0f) {
				m_flashOn = false;
				alpha = 255.0f;
			}
			m_shape.setFillColor(sf::Color(255,255,255, static_cast<sf::Uint8>(alpha)));
		}
		else {
			float alpha = static_cast<float>(m_shape.getFillColor().a) - (FLASH_SPEED * dt);
			if (alpha <= 0) {
				alpha = 0;
			}
			m_shape.setFillColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha)));
		}
	}

	void Flash::draw()
	{
		m_data->m_window.draw(m_shape);
	}
}