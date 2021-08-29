#include "Shader.h"
#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	const char* vertexShaderCode = LoadShaderFromFile(vertexPath);
	const char* fragmentShaderCode = LoadShaderFromFile(fragmentPath);

	unsigned int vertexID = CreateAndCompileShader(vertexShaderCode, GL_VERTEX_SHADER);
	unsigned int fragmentID = CreateAndCompileShader(vertexShaderCode, GL_FRAGMENT_SHADER);

	ID = CreateAndLinkProgram(vertexID, fragmentID);

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

unsigned int Shader::CreateAndLinkProgram(const unsigned int& vertexID, const unsigned int& fragmentID)
{
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);
	CheckProgramErrors(programID);

	return programID;
}

unsigned int Shader::CreateAndCompileShader(const char* shaderCode, GLenum shaderType) const
{
	// vertex shader
	unsigned int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shaderCode, NULL);
	glCompileShader(shaderID);
	CheckShaderErrors(shaderID);

	return shaderID;
}

void Shader::CheckProgramErrors(unsigned int programID) const
{
	int success;
	char infoLog[1024];
	glGetProgramiv(programID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(programID, 1024, NULL, infoLog);
		std::cout << "ERROR::PROGRAM_LINKING_ERROR:" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
}

void Shader::CheckShaderErrors(unsigned int shaderID) const
{
	int success;
	char infoLog[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shaderID, 1024, NULL, infoLog);
		std::cout << "ERROR::SHADER_COMPILATION_ERROR:" << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
	}
}

const char* Shader::LoadShaderFromFile(const char* shaderPath) const
{
	std::string shaderCode;
	std::ifstream ShaderIfStream;

	ShaderIfStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		ShaderIfStream.open(shaderPath);
		std::stringstream vertexShaderStream;

		vertexShaderStream << ShaderIfStream.rdbuf();

		ShaderIfStream.close();

		shaderCode = vertexShaderStream.str();
	}
	catch (std::ifstream::failure exception)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}

	return shaderCode.c_str();
}

void Shader::Use()
{
	glUseProgram(ID);
}

void Shader::SetBool(const std::string& boolName, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, boolName.c_str()), (int)value);
}

void Shader::SetInt(const std::string& intName, int value) const
{
	glUniform1i(glGetUniformLocation(ID, intName.c_str()), value);
}

void Shader::SetFloat(const std::string& floatName, float value) const
{
	glUniform1i(glGetUniformLocation(ID, floatName.c_str()), value);
}
