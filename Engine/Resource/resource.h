#pragma once
#include <string>

namespace vl
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;

	};
}