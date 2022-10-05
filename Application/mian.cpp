#include "engine.h"
#include <iostream>

int main(int argc, char** argv)
{
	vl::InitializeMemory();

	vl::Engine::Instance().Initialize();
	vl::Engine::Instance().Register();

	vl::g_renderer.CreateWindow("Application", 800, 600);

	float angle = 0;
	vl::Vector2 position;

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }

		vl::g_renderer.BeginFrame();




		if (vl::g_inputSystem.GetKeyState(vl::key_left) == vl::InputSystem::State::Held) 
		{ 
			position.x -= vl::g_time.deltaTime; 
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_right) == vl::InputSystem::State::Held)
		{
			position.x += vl::g_time.deltaTime;
		}
		glPushMatrix();

		angle += 45.0f * (float)vl::g_time.deltaTime;

		//glRotatef(angle , 0.0f, 0.0f, 1.0f);
		glScalef(0.5f, 0.5f, 0.5f);
		glTranslatef(position.x, position.y, 0);

		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-1.0f, -1.0f);
		//glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f(0.0f, 1.0f);
		//glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f(1.0f, -1.0f);

		glEnd();

		glPopMatrix();

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}