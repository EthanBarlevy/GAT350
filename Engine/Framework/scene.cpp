#include "scene.h"
#include "factory.h"
#include "Core/logger.h"
#include "engine.h"
#include <algorithm>

namespace vl
{
	void Scene::Initialize()
	{
		for (auto& actor : m_actors)
		{
			actor->Initialize();
		}
	}

	void Scene::Update()
	{
		auto iter = m_actors.begin();

		while (iter != m_actors.end())
		{
			(*iter)->Update();
			if ((*iter)->m_destroy)
			{
				iter = m_actors.erase(iter);
			}
			else
			{
				iter++;
			}
		}
	}

	void Scene::Draw(Renderer& renderer)
	{
		// get camera
		auto camera = GetActorFromName<Actor>("Camera");
		if (camera)
		{
			g_renderer.SetView(camera->GetComponent<CameraComponent>()->GetView());
			g_renderer.SetProjection(camera->GetComponent<CameraComponent>()->GetProjection());
		}

		// draw actors
		for (auto& actor : m_actors)
		{
			actor->Draw(renderer);
		}
	}

	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}

	void Scene::RemoveAll()
	{
		for (auto& actor : m_actors) { actor->Destroy(); }
		m_actors.clear();
	}

	bool Scene::Create(std::string name, ...)
	{
		rapidjson::Document document;
		bool sucess = vl::json::Load("scenes/texture.scn", document);
		if (!sucess)
		{
			LOG("error loading scene file %s", "scenes/basic_lit.sln");
		}
		else
		{
			Read(document);
			Initialize();
		}
		return true;
	}

	bool Scene::Write(const rapidjson::Value& value) const
	{
		return false; // im returning false because we are not implementing this
	}

	bool Scene::Read(const rapidjson::Value& value)
	{
		if (!value.HasMember("actors") || !value["actors"].IsArray())
		{
			LOG("No actors in json file");
			return false;
		}

		// read actors
		for (auto& actorValue : value["actors"].GetArray())
		{
			std::string type;
			READ_DATA(actorValue, type);
			auto actor = Factory::Instance().Create<Actor>(type);
			if (actor)
			{
				actor->Read(actorValue);

				bool prefab = false;
				READ_DATA(actorValue, prefab);

				if (prefab)
				{
					std::string name = actor->GetName();
					Factory::Instance().RegisterPrefab(name, std::move(actor));
				}
				else { Add(std::move(actor)); }

				
			}
		}

		return true;
	}
}
