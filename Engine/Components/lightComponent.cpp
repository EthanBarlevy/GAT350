#include "lightComponent.h"
#include "engine.h"

namespace vl
{
	void LightComponent::Update()
	{
		// transform the light position by the view, puts light in model view space
		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->GetTransform().position, 1);

		// get all programs in the resource system
		auto programs = g_resourceManager.Get<Program>();

		// set the direction of the transform vector
		glm::vec3 direction = m_owner->GetTransform().getForwards();

		// set programs light properties
		for (auto& program : programs)
		{
			program->SetUniform("light.type", (int)type);
			program->SetUniform("light.ambient", glm::vec3( 0.8f ));
			program->SetUniform("light.color", color);
			program->SetUniform("light.position", position);
			program->SetUniform("light.direction", direction);
			program->SetUniform("light.cutoff", glm::radians(cutoff));
			program->SetUniform("light.exponent", exponent);
		}
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, cutoff);
		READ_DATA(value, exponent);
		std::string type_name;
		READ_DATA(value, type_name);
		if (CompareIgnoreCase(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (CompareIgnoreCase(type_name, "spot"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}

		return true;
	}

}