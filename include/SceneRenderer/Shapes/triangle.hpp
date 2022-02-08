#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#include <SceneRenderer/Utility/OGLProgram.hpp>


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