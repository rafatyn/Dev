#include "AssetManager.h"

namespace Flappy {

	void AssetManager::addTexture(const char * name, const char * filename)
	{
		if (m_sounds.find(name) == m_sounds.end()) {
			sf::Texture texture;
			if (!texture.loadFromFile(filename)) {
				std::cout << "Cannot load texture with name: " << name << " and filename: " << filename << std::endl;
			}
			else {
				m_textures[name] = texture;
			}
		}
	}

	void AssetManager::addFont(const char * name, const char * filename)
	{
		if (m_sounds.find(name) == m_sounds.end()) {
			sf::Font font;
			if (!font.loadFromFile(filename)) {
				std::cout << "Cannot load font with name: " << name << ", and filename: " << filename << std::endl;
			}
			else {
				m_fonts[name] = font;
			}
		}
	}

	void AssetManager::addSound(const char * name, const char * filename)
	{
		if (m_sounds.find(name) == m_sounds.end()) {
			sf::SoundBuffer sound;
			if (!sound.loadFromFile(filename)) {
				std::cout << "Cannot load sound with name: " << name << ", and filename: " << filename << std::endl;
			}
			else {
				m_sounds[name] = sound;
			}
		}
	}

	sf::Texture& AssetManager::getTexture(const char * name)
	{
		return m_textures.at(name);
	}

	sf::Font& AssetManager::getFont(const char * name)
	{
		return m_fonts.at(name);
	}

	sf::SoundBuffer& AssetManager::getSound(const char* name)
	{
		return m_sounds.at(name);
	}

}