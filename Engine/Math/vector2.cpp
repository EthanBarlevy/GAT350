#include "vector2.h"

namespace vl
{
	const Vector2 Vector2::ONE{ 1, 1 };
	const Vector2 Vector2::ZERO{ 0, 0 };
	const Vector2 Vector2::UP{ 0, -1 };
	const Vector2 Vector2::DOWN{ 0, 1 };
	const Vector2 Vector2::LEFT{ -1, 0 };
	const Vector2 Vector2::RIGHT{ 1, 0 };

	std::istream& operator >> (std::istream& stream, Vector2& v)
	{
		std::string line;
		std::getline(stream, line);

		// { ##, ## }
		size_t start = line.find("{") + 1;
		size_t middle = line.find(",");
		size_t end = line.find("}");

		std::string xs = line.substr(start, middle - start - 1);
		v.x = std::stof(xs);

		std::string ys = line.substr(middle + 1, end - middle - 2);
		v.y = std::stof(ys);

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const Vector2& v)
	{
		stream << v.x << " " << v.y;

		return stream;
	}
}