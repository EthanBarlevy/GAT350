#pragma once
#include "document.h"
#include "Math/mathUtils.h"
#include <string>
#include <vector>

#define READ_DATA(value, data) vl::json::Get(value, #data, data)
#define READ_NAME_DATA(value, name, data) vl::json::Get(value, name, data)

namespace vl
{
	struct Vector2;
	struct Color;
	struct Rect;
}

namespace vl::json
{
	bool Load(const std::string& filename, rapidjson::Document& document);

	bool Get(const rapidjson::Value& value, const std::string& name, int& data);
	bool Get(const rapidjson::Value& value, const std::string& name, float& data);
	bool Get(const rapidjson::Value& value, const std::string& name, bool& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::string& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Vector2& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Color& data);
	bool Get(const rapidjson::Value& value, const std::string& name, Rect& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<std::string>& data);
	bool Get(const rapidjson::Value& value, const std::string& name, std::vector<int>& data);
	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec2& data);
	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec3& data);
	bool Get(const rapidjson::Value& value, const std::string& name, glm::vec4& data);

}