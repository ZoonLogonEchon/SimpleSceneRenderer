#pragma once
#include "../../glad/glad.h"
#include "opengl_program.hpp"
class MeshBuffer
{
public:
	MeshBuffer() 
		:indecesSize(0)
	{
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);
		glGenBuffers(1, &vboNormals);
		glGenVertexArrays(1, &vao);
	}
	void drawMesh()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, getIndecesSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	template<class T>
	void uploadVertexData(std::vector<T> data)
	{
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(decltype(data)::value_type) * data.size(), data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	};
	void uploadIndexData(std::vector<unsigned int> data)
	{
		indecesSize = data.size();
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(decltype(data)::value_type) * indecesSize, data.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	};
	void bind()
	{
		glBindVertexArray(vao);
	};
	void unbind()
	{
		glBindVertexArray(0);
	};
	size_t getIndecesSize()
	{
		return indecesSize;
	}
	void configureProgramAttributes(OGLProgram& program, const std::string vertex_attr_name, const std::string normals_attr_name)
	{
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		program.configureVertexAttrPtr(vertex_attr_name.c_str(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		program.enableVertexAttrArray(vertex_attr_name.c_str());
		//glBindBuffer(GL_ARRAY_BUFFER, vboNormals);
		//program.configureVertexAttrPtr(normals_attr_name.c_str(), 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
		//program.enableVertexAttrArray(normals_attr_name.c_str());
		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
private:
	GLuint vbo;
	GLuint ebo;
	GLuint vboNormals;
	GLuint vao;
	size_t indecesSize;
};