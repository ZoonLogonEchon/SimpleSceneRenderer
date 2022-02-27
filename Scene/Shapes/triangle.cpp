#include "triangle.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// todo redesign the overloaded constructors
Triangle::Triangle(const std::string name) 
	: Triangle(name, std::vector<float>({
	 0.0f,  0.0f, 1.0f,  // center
	 0.0f, 1.0f, 1.0f,  // top
	 1.0f,  0.0f, 1.0f   // right
	}))
{
	
}


Triangle::Triangle(const std::string name, const std::vector<float>& vertices)
	:name(name)
	,color(glm::vec3(0.0f, 1.0f, 1.0f))
	,position(glm::vec3(0.0f))
	,size(1.0f)
	,orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
{
	for (const auto comp : vertices)
	{
		this->vertices.push_back(comp);
	}
	face_indeces = {  // note that we start from 0!
	0, 1, 2  // first triangle
	};
	genBuffers();
}


Triangle::Triangle(const std::string name, const std::vector<std::vector<float>>& vertices)
	:name(name)
	,color(glm::vec3(0.0f, 1.0f, 1.0f))
	,position(glm::vec3(0.0f))
	,size(1.0f)
	,orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
{
	for (const auto vertex : vertices)
	{
		for (const auto comp : vertex)
		{
			this->vertices.push_back(comp);
		}
	}
	face_indeces = {  // note that we start from 0!
	0, 1, 2  // first triangle
	};
	genBuffers();
}

void Triangle::genBuffers()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
}

Triangle::~Triangle()
{
	//glDeleteBuffers(1, &m_vbo);
	//glDeleteBuffers(1, &m_ebo);
}

void Triangle::bufferData(OGLProgram& prog, const std::string attrName)
{
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * face_indeces.size(), face_indeces.data(), GL_STATIC_DRAW);
	prog.configureVertexAttrPtr(attrName.c_str(), 3, gl_type<float>::value, GL_FALSE, 0, (void*)0);
	prog.enableVertexAttrArray(attrName.c_str());
	glBindVertexArray(0);
}

void Triangle::translate(const glm::vec3 vec)
{
	position += vec;
}

void Triangle::scale(const glm::vec3 vec)
{
	size[0] *= vec[0];
	size[1] *= vec[1];
	size[2] *= vec[2];
}

void Triangle::rotate(const glm::quat q)
{
	orientation *= q;
}

glm::mat4 Triangle::getRotationMatrix()
{
	return glm::toMat4(orientation);
}

void Triangle::draw()
{
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, face_indeces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
