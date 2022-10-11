#pragma once
#include "Resource/resource.h"
#include "renderer.h"

namespace vl
{
	class Shader : public Resource
	{
	public:
		~Shader();

		virtual bool Create(std::string name, ...) override;

	public:
		GLuint m_shader = 0;
	};
}