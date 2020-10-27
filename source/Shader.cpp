#include "Shader.h"

#include <glad/glad.h>
#include "FileLoader.h"
#include <iostream>

std::unordered_map<std::string, int> puni::Shader::SHADER_CACHE;
std::unordered_map<int64_t, int> puni::Shader::MATERIAL_CACHE;

void printShaderError(std::string errmsg)
{
	std::cout << "Shader Compile Error" << std::endl;
	std::cout << errmsg << std::endl;
}

// puni::Shader::Shader(std::string vertexShaderPath, std::string fragmentShaderPath)
// {
// 	std::string vertexShader, fragmentShader;
// 	try
// 	{
// 		vertexShader = loadTextFile(vertexShaderPath);
// 		fragmentShader = loadTextFile(fragmentShaderPath);
// 		//std::cout << vertexShader << std::endl;
// 		compile(vertexShader, fragmentShader);
// 	}
// 	catch (std::exception e)
// 	{
// 		std::cout << "Failed to load VertexShader: " << vertexShaderPath << std::endl;
// 		std::cout << "Failed to load FragmentShader: " << fragmentShaderPath << std::endl;
// 	}
// }

puni::Shader::Shader()
{
	shaderID = 0;
}

puni::Shader::~Shader()
{
	// printf("Destroying Shader.\n\n");
	// printf("Deleting gl shader ID.\n\n");
	if(shaderID)
		glDeleteProgram(shaderID);
	// printf("Destroyed Shader.\n\n");		
}

unsigned int puni::Shader::ID()
{
	return shaderID;
}

void puni::Shader::use()
{
	glUseProgram(shaderID);
}

void puni::Shader::setBool(std::string paramName, bool value)
{
	glUniform1i(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void puni::Shader::setFloat(std::string paramName, float value)
{
	glUniform1f(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void puni::Shader::setInt(std::string paramName, int value)
{
	glUniform1i(glGetUniformLocation(shaderID, paramName.c_str()), value);
}

void puni::Shader::compile(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	if(shaderID)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
	auto vertexID = 0;

	if(SHADER_CACHE.find(vertexShaderPath) != SHADER_CACHE.end())
	{
		//we have it compiled already
		vertexID = SHADER_CACHE[vertexShaderPath];
	}
	else
	{
		std::string vertexShader = loadTextFile(vertexShaderPath);
		const GLchar * vS = vertexShader.c_str();

		vertexID = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexID, 1, &vS, NULL);
		glCompileShader(vertexID);
		
		int compileStatus;
		char errLog[512];
		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &compileStatus);

		if (!compileStatus)
		{
			glGetShaderInfoLog(vertexID, 512, NULL, errLog);
			printShaderError(errLog);
		}
		else
			SHADER_CACHE[vertexShaderPath] = vertexID;
	}

	auto fragmentID = 0;
	if(SHADER_CACHE.find(fragmentShaderPath) != SHADER_CACHE.end())
	{
		//we have it compiled already
		fragmentID = SHADER_CACHE[fragmentShaderPath];
	}
	else
	{
		std::string	fragmentShader = loadTextFile(fragmentShaderPath);
		const GLchar* fS = fragmentShader.c_str();

		fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentID, 1, &fS, NULL);
		glCompileShader(fragmentID);

		int compileStatus;
		char errLog[512];
		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &compileStatus);
		if (!compileStatus)
		{
			glGetShaderInfoLog(fragmentID, 512, NULL, errLog);
			printShaderError(errLog);
		}
		else
			SHADER_CACHE[fragmentShaderPath] = fragmentID;
	}
	
	int64_t matID = vertexID;
	matID = matID << 32;
	matID = matID | fragmentID;
	
	if(MATERIAL_CACHE.find(matID) != MATERIAL_CACHE.end())
		shaderID = MATERIAL_CACHE[matID];
	else
	{
		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertexID);
		glAttachShader(shaderID, fragmentID);
		glLinkProgram(shaderID);

		int compileStatus;
		char errLog[512];

		glGetProgramiv(shaderID, GL_LINK_STATUS, &compileStatus);
		if (!compileStatus)
		{
			glGetProgramInfoLog(shaderID, 512, NULL, errLog);
			printShaderError(errLog);
		}
		else
			MATERIAL_CACHE[matID] = shaderID;
	}
}


void puni::Shader::CleanUpShaderCache()
{
	for(auto& id : SHADER_CACHE)
		glDeleteShader(id.second);

	SHADER_CACHE.clear();

	for(auto& id : MATERIAL_CACHE)
		glDeleteProgram(id.second);

	MATERIAL_CACHE.clear();
}