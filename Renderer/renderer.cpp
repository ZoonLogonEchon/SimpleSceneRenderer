#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
#include "Shapes/sphere.hpp"
#include "Shaders/shaders.hpp"

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

	// phong shading program
	std::string vSSrc = Shaders::getVertexShader();
	std::string fSSrc = Shaders::getFragmentShader();

	m_prog.compileAndAttachShader(vSSrc.c_str(), GL_VERTEX_SHADER);
	m_prog.compileAndAttachShader(fSSrc.c_str(), GL_FRAGMENT_SHADER);
	m_prog.link();

	for (auto mapitem_triangle : scene.getShapes())
		mapitem_triangle.second->bufferData(m_prog, "aPos");
	// no shading program
	std::string vnss_str = Shaders::getVertexNonShadingShader();
	std::string fnss_str = Shaders::getFragmentNonShadingShader();

	nonShadingProgam.compileAndAttachShader(vnss_str.c_str(), GL_VERTEX_SHADER);
	nonShadingProgam.compileAndAttachShader(fnss_str.c_str(), GL_FRAGMENT_SHADER);
	nonShadingProgam.link();

	for (auto& mapitem_point_light : scene.getPointLights())
		mapitem_point_light.second->bufferData(nonShadingProgam, "aPos");
		

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

	// render point lights as cubes without shading (not even)

	m_prog.setUniformInt("u_num_point_lights", scene.getPointLights().size());
	int light_index = 0;
	for (auto& mapitem_point_light : scene.getPointLights())
	{
		std::string indexed_p_light_str = "u_point_lights[" + std::to_string(light_index) + "]";
		std::string indexed_p_light_position_str = indexed_p_light_str + ".position";
		std::string indexed_p_light_ambient_str = indexed_p_light_str + ".ambient";
		std::string indexed_p_light_diffuse_str = indexed_p_light_str + ".diffuse";
		std::string indexed_p_light_specular_str = indexed_p_light_str + ".specular";

		std::string indexed_p_light_kconstant_str = indexed_p_light_str + ".k_constant";
		std::string indexed_p_light_klinear_str = indexed_p_light_str + ".k_linear";
		std::string indexed_p_light_kquadratic_str = indexed_p_light_str + ".k_quadratic";
		m_prog.setUniformVector3(indexed_p_light_position_str.c_str(), mapitem_point_light.second->position);
		m_prog.setUniformVector3(indexed_p_light_ambient_str.c_str(), mapitem_point_light.second->ambient);
		m_prog.setUniformVector3(indexed_p_light_diffuse_str.c_str(), mapitem_point_light.second->diffuse);
		m_prog.setUniformVector3(indexed_p_light_specular_str.c_str(), mapitem_point_light.second->specular);

		m_prog.setUniformFloat(indexed_p_light_kconstant_str.c_str(), mapitem_point_light.second->k_constant);
		m_prog.setUniformFloat(indexed_p_light_klinear_str.c_str(), mapitem_point_light.second->k_linear);
		m_prog.setUniformFloat(indexed_p_light_kquadratic_str.c_str(), mapitem_point_light.second->k_quadratic);
		++light_index;
	}
		
	for (auto &mapitem_triangle : scene.getShapes())
		mapitem_triangle.second->draw(m_prog);
	
	// draw lights as cubes
	nonShadingProgam.use();
	nonShadingProgam.setUniformMatrix4("projection", proj);
	nonShadingProgam.setUniformMatrix4("view_transform", view_transform);

	for (auto& mapitem_point_light : scene.getPointLights())
		mapitem_point_light.second->draw(nonShadingProgam);

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
