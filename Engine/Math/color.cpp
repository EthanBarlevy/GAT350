#include "color.h"

namespace vl
{
	const Color WHITE{255, 255, 255, 255};
	const Color BLACK{0, 0, 0, 255};
	const Color RED{255, 0, 0, 255};
	const Color ORANGE{255, 132, 0, 255};
	const Color YELLOW{255, 255, 0, 255};
	const Color GREEN{0, 255, 0, 255};
	const Color BLUE{0, 0, 255, 255};
	const Color NAVY{15, 0, 102, 255};
	const Color AQUA{0, 255, 255, 255};
	const Color PURPLE{143, 0, 191, 255};
	const Color PINK{255, 75, 240, 255};
	const Color CLEAR{0, 0, 0, 0};

	std::istream& operator >> (std::istream& stream, Color& c)
	{
		std::string line;
		std::getline(stream, line);

		std::string str;
		// { #, #, #}
		str = line.substr(line.find("{") + 2, line.find(",") - (line.find("{") + 2));
		c.r = (uint8_t)(stof(str) * 255);

		str = line.substr(line.find(",") + 2, (line.find(",", line.find(",") + 1) + 2 - line.find(",") + 2));
		c.g = (uint8_t)(stof(str) * 255);

		str = line.substr(line.find(",", line.find(",") + 1) + 2, line.find("}", line.find(",", line.find(","))));
		c.b = (uint8_t)(stof(str) * 255);

		c.a = 255;

		return stream;
	}

	std::ostream& operator<<(std::ostream& stream, const Color& color)
	{
		stream << (int)color.r << " " << (int)color.g << " " << (int)color.b << " " << (int)color.a;

		return stream;
	}
}