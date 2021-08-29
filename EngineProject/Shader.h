#pragma once

#include "glad/glad.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:

	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";

	// ID of the shader program
	unsigned int ID;

	// Construction
	Shader(const char* vertexPath, const char* fragmentPath);

	// use Active Shader
	void Use();

	// Utility uniform functions
	void SetBool(const std::string& boolName, bool value) const;
	void SetInt(const std::string& boolName, int value) const;
	void SetFloat(const std::string& boolName, float value) const;

private:
	unsigned int CreateAndLinkProgram(const unsigned int& vertexID, const unsigned int& fragmentID);
	unsigned int CreateAndCompileShader(const char* shaderCode, GLenum shaderType) const;
	void CheckProgramErrors(unsigned int programID) const;
	void CheckShaderErrors(unsigned int shaderID) const;
	const char* LoadShaderFromFile(const char* shaderPath) const;

};

