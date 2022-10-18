#pragma once
#include "Math/vector2.h"
#include "Resource/resource.h"
#include "renderer.h"
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
		bool Load(const std::string& filename, Renderer& renderer);

		void Bind() { glBindTexture(m_target, m_texture); }

		Vector2 GetSize() const;

		friend class Renderer;
	private:
		void FlipSurface(SDL_Surface* surface);

	private:
		GLuint m_texture{ 0 };
		GLenum m_target{ GL_TEXTURE_2D };
		GLuint m_unit{ GL_TEXTURE0 };
		//SDL_Texture* m_texture{ nullptr };
	};
}