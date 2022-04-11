#pragma once
#include <vector>
#include <string>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include "../../OpenGLUtils/mesh_buffer.hpp"
#include "mesh_source.hpp"
#include "cube.hpp"
class Mesh
{
public:
	Mesh() 
	{
		meshSource = std::make_shared<Cube>();
		meshBuffer = std::make_shared<MeshBuffer>();
	};
	Mesh(std::shared_ptr<MeshSource> mesh_src) 
		:meshSource(mesh_src)
	{
		meshBuffer = std::make_shared<MeshBuffer>();
	};
	virtual std::vector<float> getVertexData()
	{
		return meshSource->getVertexData();
	};
	virtual std::vector<unsigned int> getFaceIndeces()
	{
		return meshSource->getFaceIndeces();
	};
	virtual std::vector<float> getNormals() 
	{
		return meshSource->getNormals();
	};
	virtual VertexInfo getVertexInfo()
	{
		return meshSource->getVertexInfo();
	}
	virtual void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
	{
		meshSource->applyObjSpaceTransformations(scale, rotation, translation);
	};
	void drawMesh()
	{
		meshBuffer->drawMesh();
	}
	void uploadData()
	{
		meshBuffer->uploadVertexData(getVertexData(), getVertexInfo());
		meshBuffer->uploadIndexData(getFaceIndeces());
	}

	GLuint getIndecesPointer()
	{
		return meshBuffer->getIndecesPointer();
	}

	GLuint getVertexArrayObject()
	{
		return meshBuffer->getVertexArrayObject();
	}

	GLuint getBufferBindingIndex()
	{
		return meshBuffer->getBufferBindingIndex();
	}

	GLuint getVertexBuffer()
	{
		return meshBuffer->getVertexBuffer();
	}

	unsigned int getVerticesAmount()
	{
		return meshSource->getVerticesAmount();
	}
protected:
	std::shared_ptr<MeshSource> meshSource;
	std::shared_ptr<MeshBuffer> meshBuffer;
};