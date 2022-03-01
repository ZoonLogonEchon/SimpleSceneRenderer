#pragma once

#include <vector>

#include "../glad/glad.h"

#include "../Scene/scene.hpp"

#include "../Scene/Shapes/triangle.hpp"
#include "../Scene/Shapes/rect.hpp"
#include "../Scene/Shapes/sphere.hpp"

#include "OGLProgram.hpp"

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