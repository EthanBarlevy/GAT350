#include "engine.h"
#include <iostream>

float points[] = {
  -0.5f, -0.5f,  0.0f,
   0.5f, -0.5f,  0.0f,
   0.5f,  0.5f,  0.0f,

   -0.5f, -0.5f,  0.0f,
   0.5f,  0.5f,  0.0f,
   -0.5f, 0.5f,  0.0f
};

glm::vec3 colors[] = {
	{1, 0, 0},
	{0, 1, 0},
	{0, 0, 1},
	{1, 0, 0},
	{0, 0, 1},
	{1, 1, 1}
};

glm::vec2 UVcoords[] = {
	{ 1, 0 },
	{ 1, 1 },
	{ 0, 1 },
	{ 1, 0 },
	{ 0, 1 },
	{ 0, 0 }
};

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

	// create vertex buffer (will probably move later)
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), UVcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);

	// create material
	std::shared_ptr<vl::Material> material = vl::g_resourceManager.Get<vl::Material>("materials/box.mtrl");
	material->Bind();
	
	glm::mat4 mx{ 1 };

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }
		
		mx = glm::eulerAngleXYZ(0.0f, 0.0f, (float)std::sin(vl::g_time.time));

		vl::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}