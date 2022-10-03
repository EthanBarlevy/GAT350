#pragma once
#include "characterComponent.h"
#include "Physics/collision.h"

namespace vl
{
	class PlayerComponent : public CharacterComponent
	{
	public:
		PlayerComponent() = default;

		CLASS_CLONE(PlayerComponent);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		
		void Initialize() override;
		void Update() override;

		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;
		virtual void OnNotify(const Event& event) override;

	public:
		float jump{ 1000 };
		float on_ground{ 0 };

		bool jumping{ false };
		bool attacking{ false };
		float attack_time{ 0 };
	};
}