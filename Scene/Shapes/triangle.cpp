#include "triangle.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


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
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);
	glGenVertexArrays(1, &m_vao);
}

Triangle::~Triangle()
{
	//glDeleteBuffers(1, &m_vbo);
	//glDeleteBuffers(1, &m_ebo);
}

void Triangle::bufferData(OGLProgram& prog, const std::string attrName)
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * face_indeces.size(), face_indeces.data(), GL_STATIC_DRAW);
	prog.configureVertexAttrPtr(attrName.c_str(), 3, gl_type<float>::value, GL_FALSE, 0, (void*)0);
	prog.enableVertexAttrArray(attrName.c_str());
	glBindVertexArray(0);
}

void Triangle::draw()
{
	glBindVertexArray(m_vao);
	glDrawElements(GL_TRIANGLES, face_indeces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
