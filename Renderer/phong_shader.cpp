#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "phong_shader.hpp"
#include "Shaders/shaders.hpp"

PhongShader::PhongShader()
{
	std::string vSSrc = Shaders::getVertexShader();
	std::string fSSrc = Shaders::getFragmentShader();
	prog = std::make_shared<OGLProgram>();
	prog->compileAndAttachShader(vSSrc.c_str(), GL_VERTEX_SHADER);
	prog->compileAndAttachShader(fSSrc.c_str(), GL_FRAGMENT_SHADER);
	prog->link();
	attributeBindingPoints["aPos"] = 0;
	attributeBindingPoints["aNormal"] = 1;
	binding_point_pos_att = 0;
	binding_point_normal_att = 1;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	// position
	auto pos_loc = prog->getAttributeLocation("aPos");
	glVertexAttribFormat(pos_loc, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(pos_loc, attributeBindingPoints["aPos"]);
	glEnableVertexAttribArray(pos_loc);
	// normals
	auto normal_loc = prog->getAttributeLocation("aNormal");
	glVertexAttribFormat(normal_loc, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexAttribBinding(normal_loc, attributeBindingPoints["aNormal"]);
	glEnableVertexAttribArray(normal_loc);
	glBindVertexArray(0);
}

PhongShader::~PhongShader()
{
}

void PhongShader::use()
{
	prog->use();
}

void PhongShader::draw(Mesh* mesh)
{
	glBindVertexArray(vao);
	//glBindVertexBuffer(attributeBindingPoints["aPos"], mesh->getPositionsPointer(), 0, 0);
	//glBindVertexBuffer(attributeBindingPoints["aNormal"], mesh->getNormalsPointer(), 0, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndecesPointer());
	glDrawElements(GL_TRIANGLES, mesh->getFaceIndeces().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void PhongShader::setAttributeBindingPoint(const char* attr_name, GLuint binding_point)
{
	glBindVertexArray(vao);
	prog->setAttributeBindingPoint(attr_name, binding_point);
	glBindVertexArray(0);
}
void PhongShader::setUniformBlockBindingPoint(const char* unif_name, GLuint binding_point)
{
	prog->setUniformBlockBindingPoint(unif_name, binding_point);
}

void PhongShader::setUniformMatrix4(const char* unif_name, const glm::mat4& mat)
{
	prog->setUniformMatrix4(unif_name, mat);
}

void PhongShader::setUniformVector3(const char* unif_name, const glm::vec3& vec)
{
	prog->setUniformVector3(unif_name, vec);
}


