#include "Hud.h"

namespace Flappy {
	
	Hud::Hud(std::shared_ptr<GameData> data) :
		m_data(data)
	{
		m_text.setFont(data->m_assets.getFont("Flappy Font"));
		m_text.setString("0");
		m_text.setCharacterSize(64);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);

		m_textShadow = m_text;

		m_text.setFillColor(sf::Color::White);
		m_text.setPosition(static_cast<float>(m_data->m_window.getSize().x / 2), static_cast<float>(data->m_window.getSize().y / 10));
		
		m_textShadow.setFillColor(sf::Color::Black);
		m_textShadow.setPosition(static_cast<float>((m_data->m_window.getSize().x / 2) + 3), static_cast<float>((data->m_window.getSize().y / 10) + 3));
	}
	
	void Hud::draw()
	{
		m_data->m_window.draw(m_textShadow);
		m_data->m_window.draw(m_text);
	}
	
	void Hud::update(int score)
	{
		m_text.setString(std::to_string(score));
		m_textShadow.setString(std::to_string(score));
	}
}