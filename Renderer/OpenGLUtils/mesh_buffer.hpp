#pragma once
#include "../../glad/glad.h"
#include "opengl_program.hpp"
#include "../typedef.hpp"
class MeshBuffer
{
public:
	MeshBuffer() 
		:indecesSize(0)
	{
		
		
		
		vboBindingIndex = 5;
	}
	void drawMesh()
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, getIndecesSize(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	void init()
	{
		glCreateBuffers(1, &vbo);
		glCreateBuffers(1, &ebo);
		glCreateVertexArrays(1, &vao);
	}
	template<class T>
	void uploadVertexData(std::vector<T> data, VertexInfo vertex_info)
	{
		// problem -> the vertex info is wrong of data doesnt fit the desc in vertex info
		
		vertex_info.vertexSize; // position + normal + etc.
		auto comp_size = sizeof(decltype(data)::value_type);
		auto comps = data.size();
		glNamedBufferStorage(vbo, comp_size * comps, data.data(), 0);
		glVertexArrayVertexBuffer(vao, vboBindingIndex, vbo, 0, vertex_info.vertexSize);
	};
	void uploadIndexData(std::vector<unsigned int> data)
	{
		indecesSize = data.size();
		glNamedBufferStorage(ebo, sizeof(decltype(data)::value_type) * indecesSize, data.data(), 0);
		glVertexArrayElementBuffer(vao, ebo);
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

	GLuint getVertexArrayObject()
	{
		return vao;
	}
	GLuint getVertexBuffer()
	{
		return vbo;
	}
	GLuint getBufferBindingIndex()
	{
		return vboBindingIndex;
	}

	GLuint getIndecesPointer()
	{
		return ebo;
	}
private:
	GLuint vbo;
	GLuint ebo;
	GLuint vao;

	GLuint vboBindingIndex;
	size_t indecesSize;
};