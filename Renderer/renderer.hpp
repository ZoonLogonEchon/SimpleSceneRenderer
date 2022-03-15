#pragma once

#include <vector>

#include "../glad/glad.h"

#include "scene.hpp"

#include "OpenGLUtils/opengl_program.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init(Scene &scene);
	void render(Scene &scene, float vp_width, float vp_height);

private:
	OGLProgram m_prog;
	OGLProgram nonShadingProgam;
	void checkGLErrors();
};