#pragma once


#include <vector>
#include <string>
#include <array>
#include "../../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../../Renderer/OGLProgram.hpp"
#include "shape.hpp"

class Triangle : public Shape
{
public:
	Triangle(const std::string name, const glm::vec3 o_scale = glm::vec3(1.0f), const glm::vec3 o_rotation = glm::vec3(0.0f), const glm::vec3 o_translation = glm::vec3(0.0f));

	~Triangle() override;

	void draw(OGLProgram& prog) override;
	void bufferData(OGLProgram &prog, const std::string attrName) override;

	void translate(const glm::vec3 vec) override;
	void scale(const glm::vec3 vec) override;
	void rotate(const glm::quat q) override;
	void setColor(const glm::vec3 col) override;
	// for convenience
	glm::mat4 getRotationMatrix();
	void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation);
private:
	GLuint vbo;
	GLuint ebo;
	GLuint vao;
	std::vector<float> vertices;
	std::vector<unsigned int> face_indeces;
	glm::vec3 normal;
	// of vertex at the right angle
	glm::vec3 position;
	glm::vec3 size;
	glm::quat orientation;
	void genBuffers();
	glm::vec3 objSpaceTransformations(glm::vec3 point, glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation);
	
};