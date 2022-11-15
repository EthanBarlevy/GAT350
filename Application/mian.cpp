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
	vl::g_gui.Initialize(vl::g_renderer);

	// load scene
	auto scene = vl::g_resourceManager.Get<vl::Scene>("scenes/texture.scn");

	glm::vec3 pos{ 0 };

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();
		vl::g_gui.BeginFrame(vl::g_renderer);

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }
		
		auto actor = scene->GetActorFromName<vl::Actor>("Ogre");
		if (actor)
		{
			//actor->GetTransform().rotation.y += (float)vl::g_time.deltaTime * 20.0f;
		}

		actor = scene->GetActorFromName<vl::Actor>("Light");
		if (actor)
		{
			actor->GetTransform().position = pos;
		}

		ImGui::Begin("hello");
		ImGui::Button("Press");
		//ImGui::SliderFloat3("position", &pos[0], -3.0f, 3.0f);
		ImGui::End();

		scene->Update();

		vl::g_renderer.BeginFrame();

		scene->PreRender(vl::g_renderer);
		scene->Render(vl::g_renderer);

		vl::g_gui.Draw();

		vl::g_renderer.EndFrame();
		vl::g_gui.EndFrame();
	}
	scene->RemoveAll();

	vl::Engine::Instance().Shutdown();
	return 0;
}