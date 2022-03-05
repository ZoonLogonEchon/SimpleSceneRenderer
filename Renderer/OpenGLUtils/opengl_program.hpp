#pragma once
#include "../../glad/glad.h"
#include <string>
#include <vector>


#include <glm/glm.hpp>

class OGLProgram
{
public:
	OGLProgram();
	~OGLProgram();

	void compileAndAttachShader(const char* src, const GLenum &shader_type);

	void link();

	void use();

	void release();

	void configureVertexAttrPtr(const char* attr_name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
	void enableVertexAttrArray(const char* attr_name);

	void setUniformMatrix4(const char* uniform_name, const glm::mat4 &mat);
	void setUniformVector3(const char* uniform_name, const glm::vec3& vec);
	void setUniformVector4(const char* uniform_name, const glm::vec4 &vec);

	//void setBool(const std::string& name, bool value);
	void setUniformInt(const char* uniform_name, const int &value);
	void setUniformFloat(const char* uniform_name, const float &value);
private:
	GLuint m_program_handle;
	std::vector<GLuint> m_shader_handles;

	void compileShader(const GLuint &shader);

};

template<typename T>
struct gl_type
{
	static const GLenum value = GL_FLOAT;
};
template<>
struct gl_type<float>
{
	static const GLenum value = GL_FLOAT;
};
template<>
struct gl_type<double>
{
	static const GLenum value = GL_DOUBLE;
};