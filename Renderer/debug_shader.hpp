#pragma once

#include <vector>

#include "../glad/glad.h"

#include "scene.hpp"

#include <set>

#include "OpenGLUtils/opengl_program.hpp"

class DebugShader
{
public:
	DebugShader();
	~DebugShader();
	void use();
	void draw(Mesh*);
	void setUniformMatrix4(const char* unif_name, const glm::mat4& mat);
	void setUniformVector3(const char* unif_name, const glm::vec3& vec);
	void configureAttributes(GLuint vao, GLuint buffer_index, VertexInfo vertex_info);
	void setUniformBlockBindingPoint(const char* unif_name, GLuint binding_point);
private:
	GLuint binding_point_pos_att;
	GLuint binding_point_normal_att;
	std::shared_ptr<OGLProgram> prog;
	std::unordered_map<std::string, GLuint> uniformBindingPoints;
	std::unordered_map<std::string, GLuint> attributeBindingPoints;
};