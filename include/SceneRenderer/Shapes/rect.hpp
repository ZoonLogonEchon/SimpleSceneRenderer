#pragma once

#include <glad/glad.h>
#include <vector>
#include <string>

#include "triangle.hpp"


#include <SceneRenderer/Utility/OGLProgram.hpp>

class Rect
{
public:
	Rect();
	~Rect();

	void draw();
	void bufferData(OGLProgram &prog, const std::string attrName);

	
private:
	std::vector<Triangle> triangles;
};