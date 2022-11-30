#pragma once
#include "Math/mathUtils.h"
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
		bool CreateTexture(int width, int height);
		bool CreateDepthTexture(int width, int height);
		bool CreateFromSurface(SDL_Surface* surface, Renderer& renderer);

		bool Load(const std::string& filename);

		void SetActive(GLuint uint) { glActiveTexture(uint); }
		void Bind() { glBindTexture(m_target, m_texture); }

		static GLenum GetInternalFormat(GLuint format);

		glm::ivec2 GetSize() const;

		friend class Renderer;
		friend class Framebuffer;

	protected:
		void FlipSurface(SDL_Surface* surface);

	protected:
		GLuint m_texture{ 0 };
		GLenum m_target{ GL_TEXTURE_2D };
		int m_width = 0;
		int m_height = 0;
	};
}