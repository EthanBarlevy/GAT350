#pragma once

namespace vl
{
	class Actor;

	class ICollidable
	{
	public:
		virtual void OnCollisionEnter(Actor* other) = 0;
		virtual void OnCollisionExit(Actor* other) = 0;
	};
}