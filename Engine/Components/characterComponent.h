#pragma once
#include "includes.h"
#include "Physics/collision.h"
#include "Framework/event.h"

namespace vl
{
	class CharacterComponent : public Component, public ICollidable, public INotify
	{
	public:
		CharacterComponent() = default;
		virtual ~CharacterComponent();

		virtual void Initialize() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		float health = 100;
		float damage = 10;
		float speed = 0;
	};

}