#pragma once
#include "Math/vector2.h"
#include "Resource/resource.h"
#include <string>

struct SDL_Texture;
struct SDL_Surface;

namespace vl
{
	class Renderer;

	class Texture : public Resource
	{
	public:
		Texture() = default;
		~Texture();

		bool Create(std::string name, ...) override;
		bool Create(Renderer& renderer, const std::string& filename);
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		Vector2 GetSize() const;

		friend class Renderer;

	private:
		SDL_Texture* m_texture{ nullptr };
	};
}