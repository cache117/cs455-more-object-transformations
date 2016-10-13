#include "transform.h"

glm::mat4 Transform::GetModel() const
{
#ifndef USE_CUSTOM_OBJECT_MATRICES
	glm::mat4 posMatrix = glm::translate(position);
	glm::mat4 rotXMatrix = glm::rotate(rotation.x, glm::vec3(1, 0, 0));
	glm::mat4 rotYMatrix = glm::rotate(rotation.y, glm::vec3(0, 1, 0));
	glm::mat4 rotZMatrix = glm::rotate(rotation.z, glm::vec3(0, 0, 1));
	glm::mat4 scaleMatrix = glm::scale(scale);
#else
	glm::mat4 posMatrix = glm::mat4(1.0f);
	posMatrix[3][0] = position.x;
	posMatrix[3][1] = position.y;
	posMatrix[3][2] = position.z;
	//
	glm::mat4 rotXMatrix = glm::mat4(1.0f);
	rotXMatrix[1][1] = cos(rotation.x);
	rotXMatrix[1][2] = sin(rotation.x);
	rotXMatrix[2][1] = -sin(rotation.x);
	rotXMatrix[2][2] = cos(rotation.x);
	//
	glm::mat4 rotYMatrix = glm::mat4(1.0f);
	rotYMatrix[0][0] = cos(rotation.y);
	rotYMatrix[0][2] = -sin(rotation.y);
	rotYMatrix[2][0] = sin(rotation.y);
	rotYMatrix[2][2] = cos(rotation.y);
	//
	glm::mat4 rotZMatrix = glm::mat4(1.0f);
	rotZMatrix[0][0] = cos(rotation.z);
	rotZMatrix[0][1] = sin(rotation.z);
	rotZMatrix[1][0] = -sin(rotation.z);
	rotZMatrix[1][1] = cos(rotation.z);
	//
	glm::mat4 scaleMatrix = glm::mat4(1.0f);
	scaleMatrix[0][0] = scale.x;
	scaleMatrix[1][1] = scale.y;
	scaleMatrix[2][2] = scale.z;
#endif // !USE_CUSTOM_OBJECT_MATRICES

	glm::mat4 rotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;
	return posMatrix * rotMatrix * scaleMatrix;
}
