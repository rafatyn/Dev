#pragma once

#include <string>
#include <iostream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace Flappy {
	
	class AssetManager
	{
	public:
		AssetManager() = default;
		~AssetManager() = default;

		void addTexture(const char* name, const char* filename);
		void addFont(const char* name, const char* filename);
		void addSound(const char* name, const char* filename);

		sf::Texture& getTexture(const char* name);
		sf::Font& getFont(const char* name);
		sf::SoundBuffer& getSound(const char* name);
	private:
		std::map<std::string, sf::Texture> m_textures;
		std::map<std::string, sf::Font> m_fonts;
		std::map<std::string, sf::SoundBuffer> m_sounds;
	};
}