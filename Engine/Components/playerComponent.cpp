#include "playerComponent.h"
#include "audioComponent.h"
#include "physicsComponent.h"
#include "collisionComponent.h"
#include "RenderComponents/spriteAnimComponent.h"
#include "Math/mathUtils.h"
#include "Framework/actor.h"
#include "Framework/scene.h"

namespace vl
{
	bool PlayerComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}
	bool PlayerComponent::Read(const rapidjson::Value& value)
	{
		CharacterComponent::Read(value);
		READ_DATA(value, jump);

		return true;
	}

	void PlayerComponent::Initialize()
	{
		CharacterComponent::Initialize();
	}

	void PlayerComponent::Update()
	{
		//if (attack_time > 0)
		//{
		//	attack_time -= (float)g_time.deltaTime;
		//}
		//else
		//{
		//	attacking = false;
		//}
		//// movement
		//Vector2 direction = Vector2::ZERO;

		//if (!attacking)
		//{
		//	if (vl::g_inputSystem.GetKeyDown(vl::key_left))
		//	{
		//		direction = Vector2::LEFT;
		//	}

		//	if (vl::g_inputSystem.GetKeyDown(vl::key_right))
		//	{
		//		direction = Vector2::RIGHT;
		//	}
		//}

		//Vector2 velocity;
		//auto component = m_owner->GetComponent<PhysicsComponent>();
		//if (component)
		//{
		//	component->ApplyForce(direction * speed);
		//	velocity = component->velocity;
		//}

		//if (vl::g_inputSystem.GetKeyState(vl::key_space) == InputSystem::State::Pressed)
		//{
		//	//
		//}

		//// jump
		//if (vl::g_inputSystem.GetKeyState(vl::key_up) == InputSystem::State::Pressed && on_ground)
		//{
		//	auto component = m_owner->GetComponent<PhysicsComponent>();
		//	if (component)
		//	{
		//		component->ApplyForce(Vector2::UP * 3000);
		//	}
		//	jumping = true;
		//}

		//if (vl::g_inputSystem.GetButtonState(vl::button_left) == InputSystem::State::Pressed && !attacking)
		//{
		//	attacking = true;
		//	attack_time = 0.3f;
		//}

		//auto animComponent = m_owner->GetComponent<SpriteAnimComponent>();
		//if (animComponent)
		//{
		//	if (velocity.x != 0) animComponent->SetFlipHorizontal(velocity.x < 0);
		//	if (!on_ground)
		//	{
		//		if (jumping)
		//		{
		//			animComponent->SetSequence("jump");
		//		}
		//		else
		//		{
		//			animComponent->SetSequence("fall");
		//		}
		//	}
		//	else
		//	{
		//		if (attacking)
		//		{
		//			animComponent->SetSequence("attack");
		//		} 
		//		else
		//		{
		//			if (std::fabs(velocity.x) > 0)
		//			{
		//				animComponent->SetSequence("run");
		//			}
		//			else
		//			{
		//				animComponent->SetSequence("idle");
		//			}
		//		}
		//	}
		//}

		//// camera stuff
		//auto camera = m_owner->GetScene()->GetActorFromName<Actor>("Camera");
		//if (camera)
		//{
		//	// instant move
		//	camera->GetTransform().position = m_owner->GetTransform().position;
		//	// smooth move
		//	//camera->GetTransform().position = math::Lerp(camera->GetTransform().position, m_owner->GetTransform().position, 2 * (float)g_time.deltaTime);
		//}
	}

	void PlayerComponent::OnCollisionEnter(Actor* other)
	{
		/*if (jumping)
		{
			jumping = false;
		}

		if (other->GetName() == "Coin")
		{
			Event event;
			event.name = "EVENT_ADD_POINTS";
			event.data = 100;

			g_eventManager.Notify(event);
			other->Destroy();
		}

		if (other->GetTag() == "Enemy")
		{
			Event event;
			event.name = "EVENT_DAMAGE";
			event.data = damage;
			event.reciever = other;

			g_eventManager.Notify(event);
		}

		if (other->GetTag() == "Ground")
		{
			on_ground++;
		}

		if (other->GetTag() == "Spawner")
		{
			Event event;
			event.name = "EVENT_SPAWN";

			g_eventManager.Notify(event);
		}*/
	}

	void PlayerComponent::OnCollisionExit(Actor* other)
	{
		/*if (other->GetTag() == "Ground")
		{
			on_ground--;
		}*/
	}

	void PlayerComponent::OnNotify(const Event& event)
	{
		/*if (event.name == "EVENT_DAMAGE")
		{
			health -= std::get<float>(event.data);
			std::cout << health << std::endl;
			if (health <= 0)
			{
				Event event;
				event.name = "EVENT_PLAYER_DEAD";

				g_eventManager.Notify(event);
			}
		}*/
	}
}


