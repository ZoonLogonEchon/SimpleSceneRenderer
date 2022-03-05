#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
#include "Shapes/sphere.hpp"
#include "Shaders/shader_sources.hpp"

Renderer::Renderer() 
{
	
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


void Renderer::init(Scene &scene)
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);

	// simple program
	std::string vSSrc = ShaderSources::getVertexShader();
	std::string fSSrc = ShaderSources::getFragmentShader();

	m_prog.compileAndAttachShader(vSSrc.c_str(), GL_VERTEX_SHADER);
	m_prog.compileAndAttachShader(fSSrc.c_str(), GL_FRAGMENT_SHADER);
	m_prog.link();

	for (auto mapitem_triangle : scene.getShapes())
		mapitem_triangle.second->bufferData(m_prog, "aPos");

	glFinish();
}


void Renderer::render(Scene& scene)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	
	const float width = 800.0f;
	const float height = 600.0f;
	Camera &mainCamera = scene.getMainCamera();
	glm::mat4 proj = mainCamera.getProjectionTransform(width, height);
	glm::mat4 view_transform = mainCamera.getViewTransform();

	m_prog.use();
	// TODO maybe there's a more efficient way to do it (avoid uploading uniform if there's no change)
	// -> uniform buffer objects
	m_prog.setUniformMatrix4("projection", proj);
	m_prog.setUniformMatrix4("view_transform", view_transform);
	m_prog.setUniformVector3("u_camera_pos", scene.getMainCamera().eye);
	for (auto &mapitem_triangle : scene.getShapes())
		mapitem_triangle.second->draw(m_prog);
	
	glDisable(GL_BLEND);
	glFinish();
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
