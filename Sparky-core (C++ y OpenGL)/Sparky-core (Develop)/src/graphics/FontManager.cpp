#include "FontManager.h"

namespace Sparky {
	namespace Graphics {

		std::vector<Font*> FontManager::Fonts_;

		void FontManager::add(Font* font)
		{
			Fonts_.push_back(font);
		}

		void FontManager::clean()
		{
			for (int i = 0; i < Fonts_.size(); i++)
				delete Fonts_[i];
		}

		Font* FontManager::get()
		{
			return Fonts_[0];
		}

		Font* FontManager::get(const std::string& name)
		{
			for (Font* ft : Fonts_)
				if (ft->getName() == name)
					return ft;

			SPARKY_WARN("[Font Manager] Font with name ", name, " not found");
			return nullptr;
		}

		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* ft : Fonts_)
				if (ft->getSize() == size && ft->getName() == name)
					return ft;

			SPARKY_WARN("[Font Manager] Font with name: ", name, " and size: ", size, " not found");
			return nullptr;
		}
	}
}