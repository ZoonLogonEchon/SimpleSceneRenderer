#pragma once

#include <vector>

#include "../glad/glad.h"

#include <set>
#include <memory>
#include "OpenGLUtils/opengl_program.hpp"
#include "Components/Meshes/mesh.hpp"
class PhongShader
{
public:
	PhongShader();
	~PhongShader();
	void use();
	void draw(Mesh*);
	void setAttributeBindingPoint(const char* attr_name, GLuint binding_point);
	void setUniformBlockBindingPoint(const char* unif_name, GLuint binding_point);
	void setUniformMatrix4(const char *unif_name, const glm::mat4 &mat);
	void setUniformVector3(const char* unif_name, const glm::vec3& vec);
private:
	GLuint vao;
	GLuint uboPV;
	GLuint uboLights;
	GLuint binding_point_pos_att;
	GLuint binding_point_normal_att;
	std::shared_ptr<OGLProgram> prog;
	std::unordered_map<std::string, GLuint> uniformBindingPoints;
	std::unordered_map<std::string, GLuint> attributeBindingPoints;

};