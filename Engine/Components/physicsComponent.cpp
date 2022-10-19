#include "physicsComponent.h"
#include "Framework/actor.h"
#include "includes.h"

namespace vl
{
	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, damping);
		READ_DATA(value, velocity);
		READ_DATA(value, acceleration);

		return true;
	}

	void PhysicsComponent::Update()
	{
		/*velocity += acceleration * (float)g_time.deltaTime;
		m_owner->GetTransform().position += velocity * (float)g_time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::ZERO;*/
	}
}
