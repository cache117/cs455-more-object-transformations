#include <string>
#include <iostream>
#include <fstream>
#include <GL\glew.h>
#include "transform.h"
#include "camera.h"

class Shader
{
public:
	Shader()
	{ }
	Shader(const std::string& fileName);
	virtual ~Shader();

	void Bind();
	void Update(const Transform& transform, const Camera& camera);
private:
	static std::string LoadShader(const std::string& fileName);
	static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	static GLuint CreateShader(const std::string& text, GLenum shaderType);

	enum
	{
		TRANSFORM_U,

		NUM_UNIFORMS
	};

	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};
