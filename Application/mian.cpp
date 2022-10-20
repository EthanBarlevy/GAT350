#include "engine.h"
#include <iostream>

// interleaved data contains position color and uv
float vertices[] = {
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f
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

	// create vertex buffer
	std::shared_ptr<vl::VertexBuffer> vb = vl::g_resourceManager.Get<vl::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 2, 8 * sizeof(float), 6 * sizeof(float));

	// create material
	std::shared_ptr<vl::Material> material = vl::g_resourceManager.Get<vl::Material>("materials/box.mtrl");
	material->Bind();
	
	glm::mat4 model{ 1 };
	glm::mat4 projection = glm::perspective(45.0f, vl::g_renderer.GetWidth() / (float)vl::g_renderer.GetHeight(), 0.01f, 100.0f);
	glm::vec3 cameraPosition{ 0, 0, 2 };

	std::vector<vl::Transform> transforms;
	for (int i = 0; i < 500; i++)
	{
		glm::vec3 u = { vl::randomf(-20, 20) , vl::randomf(-20, 20) , vl::randomf(-20, 20) };
		glm::vec3 w = { vl::randomf(360) , vl::randomf(360) , vl::randomf(360) };
		glm::vec3 o = { 1 , 1 , 1 };
		transforms.push_back(vl::Transform(u, w, o));
	}

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();
		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }
		
		// add input to move camera
		if (vl::g_inputSystem.GetKeyState(vl::key_left) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ -1 * (float)vl::g_time.deltaTime, 0, 0};
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_right) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ 1 * (float)vl::g_time.deltaTime, 0, 0 };
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_up) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ 0, 1 * (float)vl::g_time.deltaTime, 0 };
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_down) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ 0, -1 * (float)vl::g_time.deltaTime, 0 };
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_pUp) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ 0, 0, -1 * (float)vl::g_time.deltaTime };
		}
		if (vl::g_inputSystem.GetKeyState(vl::key_pDn) == vl::g_inputSystem.Held)
		{
			cameraPosition += glm::vec3{ 0, 0, 1 * (float)vl::g_time.deltaTime };
		}

		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		//model = glm::eulerAngleXYZ(0.0f, (float)(vl::g_time.time), 0.0f);

		vl::g_renderer.BeginFrame();

		for (size_t i = 0; i < transforms.size(); i++)
		{
			// update transform rotation
			transforms[i].rotation += glm::vec3{0.5, 0.5, 0.5};

			// create mvp matrix
			glm::mat4 mvp = projection * view * (glm::mat4)transforms[i];
			material->GetProgram()->SetUniform("mvp", mvp);

			vb->Draw();	
		}

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}