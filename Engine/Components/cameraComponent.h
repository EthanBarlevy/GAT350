#pragma once
#include "Framework/component.h"
#include "renderer/program.h"

namespace vl
{
	class CameraComponent : public Component
	{
	public:
		CLASS_CLONE(CameraComponent);

		virtual void Initialize() override;
		virtual void Update() override;

		void SetPerspective(float fov, float aspectRatio, float near, float far);

		void SetProgram(std::shared_ptr<Program> program);

		const glm::mat4& GetProjection() { return m_projection; }
		const glm::mat4& GetView() { return m_view; }

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		glm::mat4 m_projection{ 1 };
		glm::mat4 m_view{ 1 };
	};
}