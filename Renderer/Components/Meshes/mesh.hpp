#pragma once
#include <vector>
#include <string>
#include <array>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include "../../OpenGLUtils/mesh_buffer.hpp"
class Mesh
{
public:
	Mesh() {};
	virtual std::vector<float> getVertexData()
	{
		return std::vector<float>();
	};
	virtual std::vector<unsigned int> getFaceIndeces()
	{
		return std::vector<unsigned int>();
	};
	virtual std::vector<float> getNormals() 
	{
		return std::vector<float>();
	};
	virtual void applyObjSpaceTransformations(glm::vec3 scale, glm::vec3 rotation, glm::vec3 translation)
	{

	};
	void drawMesh()
	{
		meshBuffer->drawMesh();
	}
	void uploadData()
	{
		meshBuffer->uploadVertexData(getVertexData());
		meshBuffer->uploadVertexData(getNormals());
		meshBuffer->uploadIndexData(getFaceIndeces());
	}
	void configureProgramAttributes(OGLProgram& program, const std::string vertex_attr_name, const std::string normals_attr_name)
	{
		meshBuffer->configureProgramAttributes(program, vertex_attr_name, normals_attr_name);
	}
protected:
	std::shared_ptr<MeshBuffer> meshBuffer;
};