#pragma once
#include <chrono>
#include <unordered_map>
typedef std::chrono::milliseconds::rep EntityType;
typedef struct
{
	unsigned int vertexSize;
	std::unordered_map<std::string, unsigned int> attributeOffset;
} VertexInfo;