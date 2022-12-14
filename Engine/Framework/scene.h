#pragma once
#include "actor.h"
#include "gameObject.h"
#include "Resource/resource.h"
#include <list>
#include <memory>

namespace vl
{
	// forward decleration
	class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable, public Resource
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {};
		Scene(const Scene& other) {}
		~Scene() = default;

		CLASS_CLONE(Scene);
		virtual bool Create(std::string name, ...) override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Initialize() override;
		void Update() override;

		void PreRender(Renderer& renderer);
		void Render(Renderer& renderer);

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T>
		T* GetActorFromName(const std::string& name);

		template<typename T>
		std::vector<T*> GetActorsFromTag(const std::string& tag);


		Game* GetGame() { return m_game; }

	private:
		std::list<std::unique_ptr<Actor>> m_actors;
		Game* m_game;

	};

	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

	template<typename T>
	inline T* Scene::GetActorFromName(const std::string& name)
	{
		for (auto& actor : m_actors)
		{
			if (actor.get()->GetName() == name)
			{
				T* result = dynamic_cast<T*>(actor.get());
				if (result) return result;
			}
		}

		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> resultVec;
		for (auto& actor : m_actors)
		{
			if (actor.get()->GetTag() == tag)
			{
				T* result = dynamic_cast<T*>(actor.get());
				if (result) resultVec.push_back(result);
			}
		}

		return resultVec;
	}
}