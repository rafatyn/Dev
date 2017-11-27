#include "TextureManager.h"

namespace Sparky {
	namespace Graphics {

		std::vector<Texture*> TextureManager::Textures_;

		void TextureManager::add(Texture* texture)
		{
			Textures_.push_back(texture);
		}

		Texture* TextureManager::get(const std::string& name)
		{
			for (Texture* texture : Textures_)
				if (texture->GetName() == name)
					return texture;
			
			SPARKY_WARN("[Texture Manager] Texture not found");
			return nullptr;
		}

		void TextureManager::clean()
		{
			for (int i = 0; i < Textures_.size(); i++)
				delete Textures_[i];
		}
	}
}