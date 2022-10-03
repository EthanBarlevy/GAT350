#pragma once
#include <cstdint>
#include <iostream>
#include <string>

namespace vl
{
	//typedef unsigned char u8_t
	//using u8_t = unsigned char
	struct Color 
	{
		uint8_t r, g, b, a;

		uint8_t operator [] (size_t index) const { return (&r)[index]; }
		uint8_t& operator [] (size_t index) { return (&r)[index]; }

		static const Color WHITE;
		static const Color BLACK;
		static const Color RED;
		static const Color ORANGE;
		static const Color YELLOW;
		static const Color GREEN;
		static const Color BLUE;
		static const Color NAVY;
		static const Color AQUA;
		static const Color PURPLE;
		static const Color PINK;
		static const Color CLEAR;

		friend std::istream& operator >> (std::istream& stream, Color& c);
	};
	std::istream& operator >> (std::istream& stream, Color& c);
	std::ostream& operator << (std::ostream& stream, const Color& v);
}