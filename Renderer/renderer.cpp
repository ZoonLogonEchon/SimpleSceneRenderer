#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "renderer.hpp"

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


void Renderer::init(Scene& scene, float vp_width, float vp_height)
{
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback(MessageCallback, 0);
	//GLuint ubo;
	//glGenBuffers(1, &ubo);
	//phongShader = std::make_shared<PhongShader>();
	debugShader = std::make_shared<DebugShader>();
	// phong shading program
	//GLuint binding_point_ubo = 0;
	//GLuint binding_point_uboLights = 1;
	for (auto scene_object : scene.getSceneObjects())
	{
		auto mesh_comp = scene_object->getComponent<Mesh>();
		if (!mesh_comp)
			continue;
		mesh_comp->uploadData();
		auto vertices_amount = mesh_comp->getVerticesAmount();
		auto vertex_size = mesh_comp->getVertexInfo().vertexSize;
		void *gpudata =  malloc(vertex_size * vertices_amount);
		glGetNamedBufferSubData(mesh_comp->getVertexBuffer(), 0, vertex_size * vertices_amount, gpudata);
		float* buffer_content = reinterpret_cast<float *>(gpudata);
		debugShader->configureAttributes(mesh_comp->getVertexArrayObject(), mesh_comp->getBufferBindingIndex(), mesh_comp->getVertexInfo());
		free(gpudata);
	}
	/*
	auto mainCamera = scene.getMainCamera();
	auto cam_comp = mainCamera->getComponent<Camera>();
	auto trsf = mainCamera->getComponent<Transform>();
	auto look_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->lookDirection, 1.0f));
	auto up_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->up, 1.0f));
	auto projection = cam_comp->getProjectionTransform(vp_width, vp_height);
	glm::mat4 view_transform = glm::lookAt(trsf->position, trsf->position + glm::vec3(look_dir), glm::vec3(up_dir));

	
	
	
	unifBufferBindingPointMap[binding_point_ubo] = ubo;
	glBindBuffer(GL_UNIFORM_BUFFER, unifBufferBindingPointMap[binding_point_ubo]);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(glm::mat4), NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, binding_point_ubo, unifBufferBindingPointMap[binding_point_ubo], 0, 2 * sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, unifBufferBindingPointMap[binding_point_ubo]);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), glm::value_ptr(projection));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view_transform));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	
	GLuint uboLights;
	glGenBuffers(1, &uboLights);
	unifBufferBindingPointMap[binding_point_uboLights] = uboLights;
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	auto sizeof_pl_struct = 4 * sizeof(glm::vec3) + 3 * sizeof(glm::float32);
	assert(sizeof_pl_struct == sizeof(PointLight) + sizeof(glm::vec3));
	auto total_size = 128 * sizeof_pl_struct + sizeof(glm::int32);
	glBufferData(GL_UNIFORM_BUFFER, total_size, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBufferRange(GL_UNIFORM_BUFFER, binding_point_uboLights, uboLights, 0, total_size);
	glBindBuffer(GL_UNIFORM_BUFFER, uboLights);
	glm::int32 light_index = 0;
	for (auto scene_object : scene.getSceneObjects())
	{
		auto tr_comp = scene_object->getComponent<Transform>();
		auto pl_comp = scene_object->getComponent<PointLight>();
		if (pl_comp)
		{
			auto curr_offset = (light_index * sizeof_pl_struct) + sizeof(glm::int32);
			glBufferSubData(GL_UNIFORM_BUFFER, curr_offset, sizeof(glm::vec3), glm::value_ptr(tr_comp->position));
			glBufferSubData(GL_UNIFORM_BUFFER, curr_offset + sizeof(glm::vec3), sizeof(PointLight), pl_comp);

			++light_index;
		}
	}
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::int32), &light_index);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	
	phongShader->setUniformBlockBindingPoint("u_pv", binding_point_ubo);
	phongShader->setUniformBlockBindingPoint("u_lights", binding_point_uboLights);
	*/
	glFinish();
}

void Renderer::initEntity(EntityType entity)
{
	/*
	auto mesh_comp = ecm.getComponent<Mesh>(entity);
	auto shader_comp = ecm.getComponent<Shader>(entity);
	auto prog = shaders[shader_comp.id].program;
	mesh_comp->uploadData();
	mesh_comp.configureProgramAttributes(prog, "aPos", "aNormal");
	shaderEntityMap[shader_comp.id] = entity;
	*/
}


void Renderer::render(Scene& scene, float vp_width, float vp_height)
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const float width = vp_width;
	const float height = vp_height;
	auto mainCamera = scene.getMainCamera();
	auto cam_comp = mainCamera->getComponent<Camera>();
	auto trsf = mainCamera->getComponent<Transform>();
	auto look_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->lookDirection, 1.0f));
	auto up_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->up, 1.0f));
	auto projection = cam_comp->getProjectionTransform(vp_width, vp_height);
	glm::mat4 view_transform = glm::lookAt(trsf->position, trsf->position + glm::vec3(look_dir), glm::vec3(up_dir));

	debugShader->use();
	debugShader->setUniformMatrix4("projection", projection);
	debugShader->setUniformMatrix4("view_transform", view_transform);
	for (auto &scene_object : scene.getSceneObjects())
	{
		// this loop call code will go into the draw call itself
		auto tr_comp = scene_object->getComponent<Transform>();
		auto mesh_comp = scene_object->getComponent<Mesh>();
		if (!mesh_comp)
			continue;
		auto model_transform = tr_comp->getTransform();
		debugShader->setUniformMatrix4("model_transform", model_transform);
		//debugShader->setUniformMatrix4("u_inv_model_transform", glm::inverse(model_transform));
		//debugShader->setUniformVector3("u_obj_color", glm::vec3(1.0f, 1.0f, 0.0f));
		debugShader->draw(mesh_comp);
	}
	
	// draw lights as cubes
	//nonShadingProgam.use();
	//nonShadingProgam.setUniformMatrix4("projection", proj);
	//nonShadingProgam.setUniformMatrix4("view_transform", view_transform);

	glDisable(GL_BLEND);
	glFinish();
}

void Renderer::updateCameraStuff(Scene& scene)
{
	auto camera = scene.getMainCamera();
	auto cam_comp = camera->getComponent<Camera>();
	auto trsf = camera->getComponent<Transform>();
	auto look_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->lookDirection, 1.0f));
	auto up_dir = glm::normalize(glm::toMat4(trsf->orientation) * glm::vec4(cam_comp->up, 1.0f));
	//auto projection = cam_comp->getProjectionTransform(vp_width, vp_height);
	glm::mat4 view_transform = glm::lookAt(trsf->position, trsf->position + glm::vec3(look_dir), glm::vec3(up_dir));
	glBindBuffer(GL_UNIFORM_BUFFER, unifBufferBindingPointMap[0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), glm::value_ptr(view_transform));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
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
