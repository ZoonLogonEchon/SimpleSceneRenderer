#pragma once

#include <vector>

#include <glad/glad.h>

#include <SceneRenderer/Shapes/triangle.hpp>
#include <SceneRenderer/Shapes/rect.hpp>
#include <SceneRenderer/Shapes/sphere.hpp>

#include <SceneRenderer/Utility/OGLProgram.hpp>

typedef Sphere ParticleRenderObject;

class Renderer
{
public:
	Renderer();
	~Renderer();

	void init();
	void render();

	void updateCameraPos(const glm::vec3 &move_dir);
	GLuint getParticlesVertexBuffer();

private:
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	GLuint m_vao_dom_bounds;
	GLuint m_vbo_dom_bounds;
	GLuint m_ebo_dom_bounds;

	GLuint m_program;
	OGLProgram m_prog;

	glm::vec3 m_camera_pos;
	void checkGLErrors();
};