#pragma once
#include "Resource/resource.h" 
#include "Math/mathUtils.h" 
#include <vector> 
#include <memory> 

namespace vl
{
	class Texture;
	class Program;

	class Material : public Resource
	{
	public:
		virtual bool Create(std::string filename, ...) override;

		void Bind();

		std::shared_ptr<Program> GetProgram() { return m_program; }

	public:
		glm::vec3 color;
		float shininess = 0;
		glm::vec2 uv_tiling{ 1 };
		glm::vec2 uv_offset{ 0 };

	private:
		std::shared_ptr<Program> m_program;
		std::vector<std::shared_ptr<Texture>> m_textures;
	};
}