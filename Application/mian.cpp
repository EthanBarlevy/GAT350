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

const char* vertex_shader =
"#version 430 core\n"
"in vec3 position;"
"void main() {"
"  gl_Position = vec4(position * 1.5, 1.0);"
"}";



const char* fragment_shader =
"#version 430 core\n"
"out vec4 color;"
"void main() {"
"  color = vec4(1.0, 1.0, 1.0, 1.0);"
"}";

int main(int argc, char** argv)
{
	vl::InitializeMemory();

	vl::Engine::Instance().Initialize();
	vl::Engine::Instance().Register();

	vl::g_renderer.CreateWindow("Application", 800, 600);

	// create vertex buffer (will probably move later)
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// create shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);

	// create program
	GLuint program = glCreateProgram();
	glAttachShader(program, fs);
	glAttachShader(program, vs);
	glLinkProgram(program);
	glUseProgram(program);

	bool quit = false;
	while (!quit)
	{
		vl::Engine::Instance().Update();

		if (vl::g_inputSystem.GetKeyDown(vl::key_escape)) { quit = true; }

		vl::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		vl::g_renderer.EndFrame();
	}

	vl::Engine::Instance().Shutdown();
	return 0;
}