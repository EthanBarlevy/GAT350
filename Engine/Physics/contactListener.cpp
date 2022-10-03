#include "contactListener.h"
#include "Components/collisionComponent.h"
#include "Framework/actor.h"
#include <iostream>

namespace vl
{
	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA->GetUserData().pointer && fB->GetUserData().pointer)
		{
			Actor* aA = (Actor*)fA->GetUserData().pointer;
			Actor* aB = (Actor*)fB->GetUserData().pointer;

			if (aA->IsDestroyed() || aB->IsDestroyed()) { return; }

			if (aA->GetComponent<CollisionComponent>())
			{
				aA->GetComponent<CollisionComponent>()->OnCollisionEnter(aB);
			}
			if (aB->GetComponent<CollisionComponent>())
			{
				aB->GetComponent<CollisionComponent>()->OnCollisionEnter(aA);
			}
		}
	}

	void ContactListener::EndContact(b2Contact* contact)
	{
		b2Fixture* fA = contact->GetFixtureA();
		b2Fixture* fB = contact->GetFixtureB();

		if (fA->GetUserData().pointer && fB->GetUserData().pointer)
		{
			Actor* aA = (Actor*)fA->GetUserData().pointer;
			Actor* aB = (Actor*)fB->GetUserData().pointer;

			if (aA->IsDestroyed() || aB->IsDestroyed()) { return; }

			if (aA->GetComponent<CollisionComponent>())
			{
				aA->GetComponent<CollisionComponent>()->OnCollisionExit(aB);
			}
			if (aB->GetComponent<CollisionComponent>())
			{
				aB->GetComponent<CollisionComponent>()->OnCollisionExit(aA);
			}
		}
	}

}
