#pragma once
#include "gameObject.h"
#include "component.h"
#include <vector>
#include <memory>

namespace vl
{
	class Scene;
	class Renderer;

	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Actor& other);
		Actor(const Transform& transform) : m_transform{ transform } {}
		
		CLASS_CLONE(Actor);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Initialize() override;
		virtual void Update() override;

		virtual void Draw(Renderer& renderer);
		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }// m_model.GetRadius()* (float)std::max(m_transform.scale.x, m_transform.scale.y); }

		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& tag) { this->tag = tag; }

		const std::string& GetName() { return name; }
		void SetName(const std::string& name) { this->name = name; }

		// i know that this is bad but i dont care i like it
		Transform& GetTransform() { return m_transform; }

		void SetActive(bool active = true) { this->active = active; }
		bool IsActive() { return active; }

		void Destroy() { m_destroy = true; }
		bool IsDestroyed() { return m_destroy; }

		Scene* GetScene() { return m_scene; }

		friend class Scene;
		friend class Component;

	protected:
		Scene* m_scene{ nullptr };
		Actor* m_parent{ nullptr };
		Transform m_transform;
		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;

		std::string tag;
		std::string name;
		float lifespan{ 0 };
		bool active{ true };
		bool m_destroy{ false };
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}