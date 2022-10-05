#include "engine.h"
#include <iostream>

int main(int argc, char** argv)
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

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(0.5f, -0.5f);

		glEnd();

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}