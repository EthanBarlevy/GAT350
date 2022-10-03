#pragma once 
#include "Resource/resource.h"
#include <string>

struct _TTF_Font;
struct SDL_Surface;

namespace vl
{
	struct Color;

	class Font : public Resource
	{
	public:
		Font() = default;
		Font(const std::string& filename, int fontSize);
		~Font();

		bool Create(std::string name, ...) override ;
		SDL_Surface* CreateSurface(const std::string& text, const Color& color);
		void Load(const std::string& filename, int fontSize);

		friend class Text;
	private:
		 _TTF_Font* m_ttfFont = nullptr;
	};
}