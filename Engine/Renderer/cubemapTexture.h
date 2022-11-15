#pragma once
#include "texture.h"
#include <vector>

namespace vl
{
	class CubemapTexture : public Texture
	{
	public:
		bool Create(std::string name, ...) override;
		bool Load(const std::vector<std::string>& filenames);

	private:
		std::vector<std::string> GenerateCubeMapNames(const std::string& basename, const std::string& extension);
	};
}