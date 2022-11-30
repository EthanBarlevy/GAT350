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

	// create framebuffer texture
	auto texture = std::make_shared<vl::Texture>();
	texture->CreateTexture(512, 512);
	vl::g_resourceManager.Add<vl::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = vl::g_resourceManager.Get<vl::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();


	// load scene
	auto scene = vl::g_resourceManager.Get<vl::Scene>("scenes/rtt.scn");

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

		auto program = vl::g_resourceManager.Get<vl::Program>("Shaders/FX/re-fract-flect.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("interpolation", 0.9f);
			program->SetUniform("refraction_index", 1.5f);
		}


		ImGui::Begin("Transform");
		ImGui::DragFloat3("Rotation", &rot[0]);
		//ImGui::DragFloat("Refraction", &ri, 0.01f, 1.0, 3.0);
		ImGui::End();

		scene->Update();


		{
			auto actor = scene->GetActorFromName<vl::Actor>("RTT");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (to framebuffer)
		vl::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		vl::g_renderer.BeginFrame();
		scene->PreRender(vl::g_renderer);
		scene->Render(vl::g_renderer);
		framebuffer->Unbind();


		{
			auto actor = scene->GetActorFromName<vl::Actor>("RTT");
			if (actor)
			{
				actor->SetActive(true);
			}
		}
		// render pass 2 (to screen)
		vl::g_renderer.RestoreViewport();
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