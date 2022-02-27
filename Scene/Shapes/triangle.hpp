#pragma once


#include <vector>
#include <string>

#include "../../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include "../../Renderer/OGLProgram.hpp"


class Triangle
{
public:
	Triangle(const std::string name);
	Triangle(const std::string name, const std::vector<float> &vertices);
	Triangle(const std::string name, const std::vector<std::vector<float>>& vertices);

	~Triangle();

	void draw();
	void bufferData(OGLProgram &prog, const std::string attrName);

	void translate(const glm::vec3 vec);
	void scale(const glm::vec3 vec);

	std::string name;
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	std::vector<float> vertices;
	std::vector<unsigned int> face_indeces;
	// rgb
	glm::vec3 color;
	// of vertex at the right angle
	glm::vec3 position;
	glm::vec3 size;
	glm::quat rotation;
private:
	void genBuffers();
};