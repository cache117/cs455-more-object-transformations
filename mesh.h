#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <vector>
#include "obj_loader.h"

struct Vertex
{
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord) : pos(pos), texCoord(texCoord) 
	{ }
	glm::vec3 pos;
	glm::vec2 texCoord;
}; 

class Mesh
{
public:
	Mesh()
	{ }
	virtual ~Mesh();

	Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
	Mesh(const std::string& fileName);
	void Draw();
private:
	void InitMesh(const IndexedModel& model);

	enum
	{
		POSITION_VB, 
		TEXTCOORD_VB,
		INDEX_VB,

		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

