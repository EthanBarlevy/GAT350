#pragma once
#include "Framework/component.h"

namespace vl
{
	class LightComponent : public Component
	{
	public:
		CLASS_CLONE(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::vec3 color{ 0 };
	};
}