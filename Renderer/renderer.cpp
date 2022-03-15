#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.hpp"
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

	// no shading program
	//std::string vnss_str = Shaders::getVertexNonShadingShader();
	//std::string fnss_str = Shaders::getFragmentNonShadingShader();

	//nonShadingProgam.compileAndAttachShader(vnss_str.c_str(), GL_VERTEX_SHADER);
	//nonShadingProgam.compileAndAttachShader(fnss_str.c_str(), GL_FRAGMENT_SHADER);
	//nonShadingProgam.link();
	for (auto scene_object : scene.getSceneObjects())
	{
		auto tr_comp = scene_object.getComponent<Transform>();
		auto mesh_comp = scene_object.getComponent<Mesh>();
		if (!mesh_comp)
			continue;
		mesh_comp->uploadData();
		mesh_comp->configureProgramAttributes(m_prog, "aPos", "aNormal");
	}
	glFinish();
}


void Renderer::render(Scene& scene, float vp_width, float vp_height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const float width = vp_width;
	const float height = vp_height;
	auto &mainCamera = scene.getMainCamera();
	auto cam_comp = mainCamera.getComponent<Camera>();
	auto trsf = mainCamera.getComponent<Transform>();
	auto look_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->lookDirection, 1.0f));
	auto up_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->up, 1.0f));
	
	glm::mat4 view_transform = glm::lookAt(trsf->position, trsf->position + glm::vec3(look_dir), glm::vec3(up_dir));

	m_prog.use();
	m_prog.setUniformMatrix4("projection", cam_comp->getProjectionTransform(width, height));
	m_prog.setUniformMatrix4("view_transform", view_transform);
	m_prog.setUniformVector3("u_camera_pos", mainCamera.getComponent<Transform>()->position);

	// render point lights as cubes without shading (not even)
	int light_index = 0;
	for (auto scene_object : scene.getSceneObjects())
	{
		auto tr_comp = scene_object.getComponent<Transform>();
		auto pl_comp = scene_object.getComponent<PointLight>();
		if (pl_comp)
		{
			std::string indexed_p_light_str = "u_point_lights[" + std::to_string(light_index) + "]";
			std::string indexed_p_light_position_str = indexed_p_light_str + ".position";
			std::string indexed_p_light_ambient_str = indexed_p_light_str + ".ambient";
			std::string indexed_p_light_diffuse_str = indexed_p_light_str + ".diffuse";
			std::string indexed_p_light_specular_str = indexed_p_light_str + ".specular";

			std::string indexed_p_light_kconstant_str = indexed_p_light_str + ".k_constant";
			std::string indexed_p_light_klinear_str = indexed_p_light_str + ".k_linear";
			std::string indexed_p_light_kquadratic_str = indexed_p_light_str + ".k_quadratic";
			m_prog.setUniformVector3(indexed_p_light_position_str.c_str(), tr_comp->position);
			m_prog.setUniformVector3(indexed_p_light_ambient_str.c_str(), pl_comp->ambient);
			m_prog.setUniformVector3(indexed_p_light_diffuse_str.c_str(), pl_comp->diffuse);
			m_prog.setUniformVector3(indexed_p_light_specular_str.c_str(), pl_comp->specular);

			m_prog.setUniformFloat(indexed_p_light_kconstant_str.c_str(), pl_comp->k_constant);
			m_prog.setUniformFloat(indexed_p_light_klinear_str.c_str(), pl_comp->k_linear);
			m_prog.setUniformFloat(indexed_p_light_kquadratic_str.c_str(), pl_comp->k_quadratic);
			++light_index;
		} 
	}
	m_prog.setUniformInt("u_num_point_lights", light_index + 1);
	

	for (auto &scene_object : scene.getSceneObjects())
	{
		auto tr_comp = scene_object.getComponent<Transform>();
		auto mesh_comp = scene_object.getComponent<Mesh>();
		auto model_transform = tr_comp->getTransform();
		m_prog.setUniformMatrix4("model_transform", model_transform);
		m_prog.setUniformMatrix4("u_inv_model_transform", glm::inverse(model_transform));
		mesh_comp->drawMesh();
	}
	
	// draw lights as cubes
	//nonShadingProgam.use();
	//nonShadingProgam.setUniformMatrix4("projection", proj);
	//nonShadingProgam.setUniformMatrix4("view_transform", view_transform);

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
