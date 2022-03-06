#include "triangle.hpp"

#include <iostream>
#include <vector>
#include <random>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Triangle::Triangle(const std::string name, const glm::vec3 o_scale, const glm::vec3 o_rotation, const glm::vec3 o_translation)
	:position(glm::vec3(0.0f, 0.0f, 1.0f))
	,size(1.0f)
	,orientation(glm::quat(1.0f, 0.0f, 0.0f, 0.0f))
{
	this->name = name;
	color = glm::vec3(0.0f, 1.0f, 1.0f);
	glm::vec3 center(0.0f, 0.0f, 0.0f);
	glm::vec3 top(0.0f, 0.5f, 0.0f);
	glm::vec3 right(0.5f, 0.0f, 0.0f);
	//center = objSpaceTransformations(center, o_scale, o_rotation, o_translation);
	//top = objSpaceTransformations(top, o_scale, o_rotation, o_translation);
	//right = objSpaceTransformations(right, o_scale, o_rotation, o_translation);
	std::vector<float> t({
		center[0], center[1], center[2],  // center
		top[0], top[1], top[2],  // top
		right[0],  right[1], right[2]   // right
	});
	
	vertices = t;
	applyObjSpaceTransformations(o_scale, o_rotation, o_translation);
	face_indeces = {  // note that we start from 0!
		0, 1, 2  // first triangle
	};
	
	center = glm::vec3(vertices[0], vertices[1], vertices[2]);
	top = glm::vec3(vertices[3], vertices[4], vertices[5]);
	right = glm::vec3(vertices[6], vertices[7], vertices[8]);
	glm::vec3 side_a = glm::normalize(top - center);
	glm::vec3 side_c = glm::normalize(right - center);
	normal = glm::normalize(glm::cross(side_c, side_a));
	genBuffers();
}

glm::vec3 Triangle::objSpaceTransformations(glm::vec3 point, glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	glm::vec4 p(point, 1.0f);
	glm::quat q_rot(rotation);
	glm::vec4 s_p = glm::scale(glm::mat4(1.0f), scale) * p;
	glm::vec4 rs_p = glm::toMat4(q_rot) * s_p;
	glm::vec4 trs_p = glm::translate(glm::mat4(1.0f), translation) * rs_p;
	return glm::vec3(trs_p);
}

void Triangle::genBuffers()
{
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);
}

Triangle::~Triangle()
{
	//glDeleteBuffers(1, &vbo);
	//glDeleteBuffers(1, &ebo);
	//glDeleteVertexArrays(1, &vao);
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

void Triangle::setColor(const glm::vec3 col)
{
	color = col;
}

glm::mat4 Triangle::getRotationMatrix()
{
	return glm::toMat4(orientation);
}

void Triangle::applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
{
	glm::vec3 center(vertices[0], vertices[1], vertices[2]);
	glm::vec3 top(vertices[3], vertices[4], vertices[5]);
	glm::vec3 right(vertices[6], vertices[7], vertices[8]);
	center = objSpaceTransformations(center, scale, rotation, translation);
	top = objSpaceTransformations(top, scale, rotation, translation);
	right = objSpaceTransformations(right, scale, rotation, translation);
	std::vector<float> t({
		center[0], center[1], center[2],  // center
		top[0], top[1], top[2],  // top
		right[0],  right[1], right[2]   // right
	});
	vertices = t;
	center = glm::vec3(vertices[0], vertices[1], vertices[2]);
	top = glm::vec3(vertices[3], vertices[4], vertices[5]);
	right = glm::vec3(vertices[6], vertices[7], vertices[8]);
	glm::vec3 side_a = glm::normalize(top - center);
	glm::vec3 side_c = glm::normalize(right - center);
	normal = glm::normalize(glm::cross(side_c, side_a));
}

void Triangle::draw(OGLProgram &prog)
{
	prog.setUniformVector3("u_obj_color", color);
	glm::mat4 model_transform = glm::mat4(1.0f);
	model_transform = glm::translate(model_transform, position);
	model_transform = glm::scale(model_transform,size);
	model_transform = model_transform * getRotationMatrix();
	prog.setUniformMatrix4("model_transform", model_transform);
	prog.setUniformVector3("u_normal", normal);
	prog.setUniformMatrix4("u_inv_model_transform", glm::inverse(model_transform));
	prog.use();
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, face_indeces.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
