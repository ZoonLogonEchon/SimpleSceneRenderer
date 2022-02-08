#include <iostream>

#include "SceneRenderer/Utility/OGLProgram.hpp"

OGLProgram::OGLProgram()
	:m_program_handle(glCreateProgram())
{
	
}

OGLProgram::~OGLProgram()
{
	for (GLuint shader : m_shader_handles)
	{
		glDeleteShader(shader);
	}
	glDeleteProgram(m_program_handle);
}

void OGLProgram::compileAndAttachShader(const char *src, const GLenum& shader_type)
{
	GLuint shader_handle = glCreateShader(shader_type);
	glShaderSource(shader_handle, 1, &src, NULL);
	compileShader(shader_handle);
	glAttachShader(m_program_handle, shader_handle);
	m_shader_handles.push_back(shader_handle);
}

void OGLProgram::link()
{
	int  success;
	char infoLog[512];
	glLinkProgram(m_program_handle);
	glGetProgramiv(m_program_handle, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_program_handle, 512, NULL, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
}

void OGLProgram::use()
{
	glUseProgram(m_program_handle);
}

void OGLProgram::release()
{
	glUseProgram(0);
}

void OGLProgram::configureVertexAttrPtr(const char* attr_name, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
	GLuint location_aPos = glGetAttribLocation(m_program_handle, attr_name);
	glVertexAttribPointer(location_aPos, size, type, normalized, stride, pointer);
}

void OGLProgram::enableVertexAttrArray(const char* attr_name)
{
	GLuint location_aPos = glGetAttribLocation(m_program_handle, attr_name);
	glEnableVertexAttribArray(location_aPos);
}

void OGLProgram::setUniformMatrix4(const char* uniform_name, const glm::mat4& mat)
{
	
	GLint uni_proj_loc = glGetUniformLocation(m_program_handle, uniform_name); 
	glUniformMatrix4fv(uni_proj_loc, 1, GL_FALSE, &mat[0][0]);
}

void OGLProgram::setUniformVector4(const char* uniform_name, const glm::vec4& vec)
{
	GLint uni_proj_loc = glGetUniformLocation(m_program_handle, uniform_name);
	glUniform4fv(uni_proj_loc, 1, &vec[0]);
}

void OGLProgram::setUniformFloat(const char* uniform_name, const float& value)
{
	GLint uni_proj_loc = glGetUniformLocation(m_program_handle, uniform_name);
	glUniform1f(uni_proj_loc, value);
}

void OGLProgram::compileShader(const GLuint& shader_handle)
{
	glCompileShader(shader_handle);
	int  success;
	char infoLog[512];
	glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader_handle, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
}
