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
	float ri = 1.5f;

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

		auto program = vl::g_resourceManager.Get<vl::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}


		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		ImGui::DragFloat("Refraction", &ri, 0.01f, 1.0, 3.0);
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