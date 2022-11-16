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
	auto scene = vl::g_resourceManager.Get<vl::Scene>("scenes/cubemap.scn");

	glm::vec3 rot{ 0 };

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();
		vl::g_gui.BeginFrame(vl::g_renderer);

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }
		
		auto actor = scene->GetActorFromName<vl::Actor>("Model");
		if (actor)
		{
			actor->GetTransform().rotation = math::EulerToQuaternion(rot);
		}

		actor = scene->GetActorFromName<vl::Actor>("Light");
		if (actor)
		{
			//actor->GetTransform().position = rot;
		}

		ImGui::Begin("Transform");
		ImGui::SliderFloat3("Rotation", &rot[0], -360.0f, 360.0f);
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