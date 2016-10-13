#pragma once

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>

#define USE_CUSTOM_OBJECT_MATRICES

struct Transform
{
	Transform(const glm::vec3& pos = glm::vec3(), const glm::vec3& rot = glm::vec3(), const glm::vec3& scale = glm::vec3(1.0f, 1.0f, 1.0f)) : position(pos), rotation(rot), scale(scale)
	{ }
	virtual ~Transform()
	{ }

	glm::mat4 GetModel() const;

	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec3 scale;
};

