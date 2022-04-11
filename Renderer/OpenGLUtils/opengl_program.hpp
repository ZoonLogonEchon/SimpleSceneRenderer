#pragma once
#include "../../glad/glad.h"
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <unordered_map>
class OGLProgram
{
public:
	OGLProgram();
	~OGLProgram();

	void compileAndAttachShader(const char* src, const GLenum &shader_type);

	void link();

	void use();

	void release();

	GLuint getAttributeLocation(const char* attr_name);
	void configureVertexAttrPtr(const char* attr_name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
	void enableVertexAttrArray(const char* attr_name);

	// if the name doens't exist the program doesn't fail
	void setUniformMatrix4(const char* uniform_name, const glm::mat4 &mat);
	void setUniformVector3(const char* uniform_name, const glm::vec3& vec);
	void setUniformVector4(const char* uniform_name, const glm::vec4 &vec);

	//void setBool(const std::string& name, bool value);
	void setUniformInt(const char* uniform_name, const int &value);
	void setUniformFloat(const char* uniform_name, const float &value);

	GLuint getUniformBlockIndex(const char* uniform_block_name);

	void setUniformBlockBindingPoint(const char* uniform_block_name, GLuint binding_point);
	void setAttributeBindingPoint(const char* attr_name, GLuint binding_point);
private:
	GLuint m_program_handle;
	std::vector<GLuint> m_shader_handles;
	void compileShader(const GLuint &shader);

};