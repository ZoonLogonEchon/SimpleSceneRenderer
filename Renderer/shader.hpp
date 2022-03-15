#pragma once

#include <vector>

#include "../glad/glad.h"

#include "scene.hpp"

#include <set>

#include "OpenGLUtils/opengl_program.hpp"

class Shader
{
public:
	Shader();
	~Shader();

	void init();
	void render();

	void addRenderableEntity(unsigned int ent);
	void addLightEntity(unsigned int ent);
	void setCameraEntity(unsigned int ent);
private:
	unsigned int cameraEntity;
	std::set<unsigned int> renderableEntities;
	std::set<unsigned int> lightEntities;
};