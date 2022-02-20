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
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	GLuint m_vao_dom_bounds;
	GLuint m_vbo_dom_bounds;
	GLuint m_ebo_dom_bounds;

	Triangle tr;
	OGLProgram m_prog;

	void checkGLErrors();
};