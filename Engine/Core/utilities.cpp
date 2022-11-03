#include "utilities.h"
#include <algorithm>

namespace vl
{
	std::string ToLower(const std::string& str)
	{
		std::string lower = str;
		
		std::transform(lower.begin(), lower.end(), lower.begin(), [](unsigned char c) {return std::tolower(c); });

		return lower;
	}

	std::string ToUpper(const std::string& str)
	{
		std::string upper = str;

		std::transform(upper.begin(), upper.end(), upper.begin(), [](unsigned char c) {return std::toupper(c); });

		return upper;
	}

	bool CompareIgnoreCase(const std::string& str1, const std::string& str2)
	{
		return ToLower(str1) == ToLower(str2);
	}
}
