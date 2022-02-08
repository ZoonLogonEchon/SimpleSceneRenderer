#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "SceneRenderer/renderer.hpp"
#include "SceneRenderer/Shapes/sphere.hpp"
#include "SceneRenderer/Shaders/shaderSources.hpp"

Renderer::Renderer() 
{
	m_camera_pos[0] = { 0/*-32*/ };
	m_camera_pos[1] = { 0/*-12*/ };
	m_camera_pos[2] = { 0/*-100*/ };
}

Renderer::~Renderer()
{
}
void GLAPIENTRY
MessageCallback(GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam)
{
	fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
		(type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
		type, severity, message);
}


void Renderer::init()
{
	m_camera_pos[0] = 0.0;//-(dom.x_max - dom.x_min) / 2.0;
	m_camera_pos[1] = 0.0;// -(dom.y_max - dom.y_min) / 2.0;
	m_camera_pos[2] = -20.0;
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);


	// for particles
	std::string particleVSSrc = ShaderSources::getParticleVertexShader();
	std::string particleFSSrc = ShaderSources::getParticleFragmentShader();

	// simple program
	std::string vSSrc = ShaderSources::getVertexShader();
	std::string fSSrc = ShaderSources::getFragmentShader();

	m_prog.compileAndAttachShader(vSSrc.c_str(), GL_VERTEX_SHADER);
	m_prog.compileAndAttachShader(fSSrc.c_str(), GL_FRAGMENT_SHADER);
	m_prog.link();

	glFinish();
}

GLuint Renderer::getParticlesVertexBuffer()
{
	return m_vbo;
}

void Renderer::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_PROGRAM_POINT_SIZE);
	glPointSize(1.f);
	
	// camera settings
	const float fovy = 20.0f;
	int viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	float aspect = viewport[2] / viewport[3];
	const float z_near = 0.01f;
	const float z_far = 100.0f;
	glm::mat4 proj = glm::perspective(fovy, aspect, z_near, z_far);
	glm::mat4 view_transform(1.0);
	view_transform = glm::translate(view_transform, m_camera_pos);

	// volume bounds
	m_prog.use();
	m_prog.setUniformMatrix4("projection", proj);
	m_prog.setUniformMatrix4("view_transform", view_transform);
	
	//glDisable(GL_POINT_SIZE);
	glDisable(GL_BLEND);
	glFinish();
}

void Renderer::updateCameraPos(const glm::vec3& move_dir)
{
	m_camera_pos += move_dir;
}

void Renderer::checkGLErrors()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::string err_str;
		switch (err)
		{
		case GL_INVALID_OPERATION:
			err_str = "GL_INVALID_OPERATION";
			break;
		case GL_OUT_OF_MEMORY:
			err_str = "GL_OUT_OF_MEMORY";
			break;
		case GL_INVALID_ENUM:
			err_str = "GL_INVALID_ENUM";
			break;
		default:
			err_str = "some other error";
			break;
		}
		std::cout << err_str << std::endl;
	}
}
