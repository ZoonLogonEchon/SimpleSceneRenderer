#pragma once

#include <vector>

#include "../glad/glad.h"

#include "scene.hpp"

#include "Shapes/triangle.hpp"
#include "Shapes/rect.hpp"
#include "Shapes/sphere.hpp"

#include "OpenGLUtils/opengl_program.hpp"

typedef Sphere ParticleRenderObject;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init(Scene &scene);
	void render(Scene &scene);

private:

	OGLProgram m_prog;

	void checkGLErrors();
};