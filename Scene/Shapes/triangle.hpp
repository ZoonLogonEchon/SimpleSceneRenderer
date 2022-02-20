#pragma once


#include <vector>
#include <string>

#include "../../glad/glad.h"
#include <glm/glm.hpp>

#include "../../Renderer/OGLProgram.hpp"


class Triangle
{
public:
	Triangle();
	Triangle(const std::vector<float> &vertices);
	Triangle(const std::vector<std::vector<float>> &vertices);
	~Triangle();

	void draw();
	void bufferData(OGLProgram &prog, const std::string attrName);

	
private:
	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;
	std::vector<float> vertices;
	std::vector<unsigned int> face_indeces;
	void genBuffers();
};