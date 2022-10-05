#include "engine.h"
#include <iostream>

int main()
{
	vl::InitializeMemory();

	vl::Engine::Instance().Initialize();
	vl::Engine::Instance().Register();

	vl::g_renderer.CreateWindow("Application", 800, 600);

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }

		vl::g_renderer.BeginFrame();

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
}