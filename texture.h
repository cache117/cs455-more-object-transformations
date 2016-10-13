#pragma once

#include <string>
#include <GL\glew.h>
#include <cassert>
#include <iostream>
#include "stb_image.h"

class Texture
{
public:
	Texture()
	{ }
	Texture(const std::string& fileName);

	void Bind(unsigned int unit);

	virtual ~Texture();

private:
	GLuint m_texture;
};

