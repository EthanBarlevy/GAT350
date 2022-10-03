#pragma once
#include "includes.h"
#include "Math/vector2.h"

namespace vl
{
	class PhysicsComponent : public Component
	{
	public:
		PhysicsComponent() = default;

		CLASS_CLONE(PhysicsComponent);
		
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update() override;
		virtual void ApplyForce(const Vector2& force) { acceleration += force; }

	public:
		Vector2 velocity{ Vector2::ZERO };
		Vector2 acceleration{ Vector2::ZERO };

		float damping{ 0.7f };
	};
}