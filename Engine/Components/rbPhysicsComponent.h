#pragma once
#include "physicsComponent.h"

namespace vl
{
	class RBPhysicsComponent : public PhysicsComponent
	{
	public:
		RBPhysicsComponent() = default;
		~RBPhysicsComponent();

		CLASS_CLONE(RBPhysicsComponent);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Initialize() override;
		void Update() override;
		virtual void ApplyForce(const Vector2& force);

		friend class CollisionComponent;

	private:
		PhysicsSystem::RigidBodyData data;
		b2Body* m_body{ nullptr };
	};
}