#pragma once
#include "Framework/component.h"

namespace vl
{
	class LightComponent : public Component
	{
	public:
		CLASS_CLONE(LightComponent)

		enum Type
		{
			Point,
			Directional,
			Spot
		};

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 color{ 0 };
		Type type = Type::Point;
		float cutoff = 45.0f;
		float exponent = 50.0f;
	};
}