#pragma once
#include "Math/transform.h"
#include "Serialization/serializable.h"

#define REGISTER_CLASS(class) vl::Factory::Instance().Register<class>(#class);
#define CLASS_CLONE(class) std::unique_ptr<GameObject> Clone() override { return std::make_unique<class>(*this); }

namespace vl
{
	class GameObject
	{
	public:
		GameObject() = default;

		virtual void Initialize() = 0;
		virtual void Update() = 0;
		virtual std::unique_ptr<GameObject> Clone() = 0;
	};
}