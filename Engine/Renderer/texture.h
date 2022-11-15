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

		bool Load(const std::string& filename);

		void SetActive(GLuint uint) { glActiveTexture(uint); }
		void Bind() { glBindTexture(m_target, m_texture); }

		static GLenum GetInternalFormat(GLuint format);

		Vector2 GetSize() const;

		friend class Renderer;

	protected:
		void FlipSurface(SDL_Surface* surface);

	protected:
		GLuint m_texture{ 0 };
		GLenum m_target{ GL_TEXTURE_2D };
	};
}