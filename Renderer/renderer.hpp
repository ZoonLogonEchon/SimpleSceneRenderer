#pragma once

#include <vector>

#include "../glad/glad.h"

#include "scene.hpp"
#include "phong_shader.hpp"
#include "debug_shader.hpp"
#include "OpenGLUtils/opengl_program.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init(Scene &scene, float vp_width, float vp_height);
	void initEntity(EntityType entity);
	void render(Scene &scene, float vp_width, float vp_height);
	void updateCameraStuff(Scene& scene);
private:
	//OGLProgram m_prog;
	//std::shared_ptr<PhongShader> phongShader;
	GLuint uboVP;
	std::shared_ptr<DebugShader> debugShader;
	std::unordered_map<GLuint, GLuint> unifBufferBindingPointMap;
	void checkGLErrors();
};