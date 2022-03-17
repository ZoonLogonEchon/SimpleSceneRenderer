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
		meshBuffer->uploadVertexData(getVertexData());
		//meshBuffer->uploadVertexData(getNormals());
		meshBuffer->uploadIndexData(getFaceIndeces());
	}
	void configureProgramAttributes(OGLProgram& program, const std::string vertex_attr_name, const std::string normals_attr_name)
	{
		meshBuffer->configureProgramAttributes(program, vertex_attr_name, normals_attr_name);
	}
protected:
	std::shared_ptr<MeshSource> meshSource;
	std::shared_ptr<MeshBuffer> meshBuffer;
};