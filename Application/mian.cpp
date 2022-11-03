#include "engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	LOG("Application Started...");
	vl::InitializeMemory();
	vl::SetFilePath("../Assets");

	vl::Engine::Instance().Initialize();
	vl::Engine::Instance().Register();
	LOG("Engine Initialized...");

	vl::g_renderer.CreateWindow("Application", 800, 600);
	LOG("Window Initialized...");

	// load scene
	auto scene = std::make_unique<vl::Scene>();
	rapidjson::Document document;
	bool sucess = vl::json::Load("scenes/texture.scn", document);
	if (!sucess)
	{
		LOG("error loading scene file %s", "scenes/basic_lit.sln");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();
		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }
		
		auto actor = scene->GetActorFromName<vl::Actor>("Ogre");
		if (actor)
		{
			actor->GetTransform().rotation.y += (float)vl::g_time.deltaTime * 20.0f;
		}

		auto material = vl::g_resourceManager.Get<vl::Material>("Materials/multi.mtrl");
		if (material)
		{
			//material->uv_offset.x += vl::g_time.deltaTime / 2;
			//material->uv_offset.y -= vl::g_time.deltaTime;
		}

		scene->Update();

		vl::g_renderer.BeginFrame();

		scene->Draw(vl::g_renderer);

		vl::g_renderer.EndFrame();
	}
	scene->RemoveAll();

	vl::Engine::Instance().Shutdown();
	return 0;
}