#include "Bird.h"

namespace Flappy {
	
	Bird::Bird(std::shared_ptr<GameData> data) :
		m_data(data), m_animationFrames(0)
	{
		m_animationFrames.push_back(m_data->m_assets.getTexture("Bird Frame 1"));
		m_animationFrames.push_back(m_data->m_assets.getTexture("Bird Frame 2"));
		m_animationFrames.push_back(m_data->m_assets.getTexture("Bird Frame 3"));
		m_animationFrames.push_back(m_data->m_assets.getTexture("Bird Frame 4"));

		m_birdSprite.setTexture(m_animationFrames[m_animationIterator]);
		m_birdSprite.setScale(SCREEN_SCALE_WIDTH, SCREEN_SCALE_HEIGHT);

		m_birdSprite.setPosition((m_data->m_window.getSize().x / 4) - (m_birdSprite.getGlobalBounds().width / 2), 
								 (m_data->m_window.getSize().y / 4) - (m_birdSprite.getGlobalBounds().height / 2));

		m_birdSprite.setOrigin(m_birdSprite.getGlobalBounds().width / 2, m_birdSprite.getGlobalBounds().height / 2);

		m_birdState = BIRD_STATE_STILL;
		m_rotation = 0;
	}

	void Bird::draw()
	{
		m_data->m_window.draw(m_birdSprite);
	}

	void Bird::animate(float dt)
	{
		if (m_clock.getElapsedTime().asSeconds() >= BIRD_ANIMATION_DURATION / m_animationFrames.size()) {
			m_animationIterator = (m_animationIterator + 1) % m_animationFrames.size();
			m_birdSprite.setTexture(m_animationFrames[m_animationIterator]);
			m_clock.restart();
		}
	}

	void Bird::update(float dt)
	{
		if (m_birdState == BIRD_STATE_FALLING) {
			m_birdSprite.move(0, GRAVITY * dt);

			m_rotation = (m_rotation > 25.0f ? 25.0f : m_rotation + (ROTATION_SPEED * dt));
			
			m_birdSprite.setRotation(m_rotation);
		}
		else if (m_birdState == BIRD_STATE_FLYING) {
			m_birdSprite.move(0, -FLYING_SPEED * dt);

			if (m_birdSprite.getPosition().y < 0 + (m_birdSprite.getGlobalBounds().height / 2)) {
				m_birdSprite.setPosition(m_birdSprite.getPosition().x, m_birdSprite.getGlobalBounds().height / 2);
			}

			m_rotation = (m_rotation < -25.0f ? -25.0f : m_rotation - (ROTATION_SPEED * dt));

			m_birdSprite.setRotation(m_rotation);
		}
		
		if (m_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION) {
			m_movementClock.restart();
			m_birdState = BIRD_STATE_FALLING;
		}
	}

	void Bird::tap()
	{
		m_movementClock.restart();
		m_birdState = BIRD_STATE_FLYING;
	}

	const sf::Sprite& Bird::getSprite() const
	{
		return m_birdSprite;
	}

}