#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "debug_shader.hpp"
#include "Shaders/shaders.hpp"

DebugShader::DebugShader()
{
	std::string vSSrc = Shaders::getVertexNonShadingShader();
	std::string fSSrc = Shaders::getFragmentNonShadingShader();
	prog = std::make_shared<OGLProgram>();
	prog->compileAndAttachShader(vSSrc.c_str(), GL_VERTEX_SHADER);
	prog->compileAndAttachShader(fSSrc.c_str(), GL_FRAGMENT_SHADER);
	prog->link();
	attributeBindingPoints["aPos"] = 0;

}

DebugShader::~DebugShader()
{
}

void DebugShader::use()
{
	prog->use();
}

void DebugShader::draw(Mesh* mesh)
{
	glBindVertexArray(mesh->getVertexArrayObject());
	//glBindVertexArray(vao);
	//glBindVertexBuffer(attributeBindingPoints["aPos"], mesh->getPositionsPointer(), 0, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, mesh->getPositionsPointer());
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIndecesPointer());
	glDrawElements(GL_TRIANGLES, mesh->getFaceIndeces().size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DebugShader::setUniformMatrix4(const char* unif_name, const glm::mat4& mat)
{
	prog->setUniformMatrix4(unif_name, mat);
}

void DebugShader::setUniformVector3(const char* unif_name, const glm::vec3& vec)
{
	prog->setUniformVector3(unif_name, vec);
}

void DebugShader::configureAttributes(GLuint vao, GLuint buffer_index, VertexInfo vertex_info)
{
	auto pos_loc = prog->getAttributeLocation("aPos");
	glVertexArrayAttribFormat(vao, pos_loc, 3, GL_FLOAT, GL_FALSE, vertex_info.attributeOffset["position"]);
	glVertexArrayAttribBinding(vao, pos_loc, buffer_index);
	glEnableVertexArrayAttrib(vao, pos_loc);

	auto normal_loc = prog->getAttributeLocation("aNormal");
	glVertexArrayAttribFormat(vao, normal_loc, 3, GL_FLOAT, GL_FALSE, vertex_info.attributeOffset["normal"]);
	glVertexArrayAttribBinding(vao, normal_loc, buffer_index);
	glEnableVertexArrayAttrib(vao, normal_loc);
	
}

void DebugShader::setUniformBlockBindingPoint(const char* unif_name, GLuint binding_point)
{
	prog->setUniformBlockBindingPoint(unif_name, binding_point);
}

