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

int main(int argc, char** argv)
{
	vl::InitializeMemory();
	vl::SetFilePath("../Assets");

	vl::Engine::Instance().Initialize();
	vl::Engine::Instance().Register();

	vl::g_renderer.CreateWindow("Application", 800, 600);

	// create vertex buffer (will probably move later)
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

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

	// create shader
	std::shared_ptr<vl::Shader> vs = vl::g_resourceManager.Get<vl::Shader>("Shaders/basic.vert", GL_VERTEX_SHADER);
	std::shared_ptr<vl::Shader> fs = vl::g_resourceManager.Get<vl::Shader>("Shaders/basic.frag", GL_FRAGMENT_SHADER);

	//GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//glShaderSource(vs, 1, &vertex_shader, NULL);
	//glCompileShader(vs);
	//GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fs, 1, &fragment_shader, NULL);
	//glCompileShader(fs);

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, vs->m_shader);
	glAttachShader(program, fs->m_shader);
	glLinkProgram(program);
	glUseProgram(program);

	GLint uniform1 = glGetUniformLocation(program, "scale");
	GLint uniform2 = glGetUniformLocation(program, "tint");
	GLint uniform3 = glGetUniformLocation(program, "transform");

	glUniform3f(uniform2, 1, 1, 1);
	

	glm::mat4 mx{ 1 };

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }

		glUniform1f(uniform1, std::sin(vl::g_time.time));
		mx = glm::eulerAngleXYZ(0.0f, 0.0f, (float)std::sin(vl::g_time.time));
		glUniformMatrix4fv(uniform3, 1, GL_FALSE, glm::value_ptr(mx));

		vl::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}