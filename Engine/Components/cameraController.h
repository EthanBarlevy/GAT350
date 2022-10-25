#pragma once
#include "Framework/component.h"

namespace vl
{
	class CameraController : public Component
	{
	public:
		CLASS_CLONE(CameraController);

		void Update() override;
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		float speed = 0;
	};
}