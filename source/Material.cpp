#include "Material.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include "Vertex.h"
#include <stdio.h>

puni::Material::Material()
{
	//shader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
	shader = 0;
	texture = 0;
	createDefaultAttributes();
}

puni::Material::Material(std::string vertexShaderPath, std::string fragmentShaderPath)
{
	loadShader(vertexShaderPath, fragmentShaderPath);
	createDefaultAttributes();
}

puni::Material::Material(Shader * const preMadeShader)
{
	shader = preMadeShader;
	createDefaultAttributes();
}


puni::Material::~Material()
{
	delete shader;
	delete texture;
}

unsigned int puni::Material::shaderID()
{
	return shader->ID();
}

void puni::Material::loadShader(std::string vertP, std::string fragP)
{
	if(shader)
	{
		printf("deleting material shader...\n\n");
		delete shader;
		shader = 0;
	}
	printf("making material shader...\n\n");
	shader = new Shader();
	printf("compiling material shader...\n\n");
	shader->compile(vertP, fragP);
}

void puni::Material::setAttributes(const VertexAttributes * attribs, unsigned int attribCount)
{
	attributes.clear();
	attributes.insert(attributes.begin(), attribs, attribs + attribCount);
}

void puni::Material::setShader(Shader * const sh)
{
	delete shader;
	shader = 0;
	shader = sh;
}

void puni::Material::setTexture(Texture * const tx)
{
	if (texture != nullptr)
		delete texture;
	texture = tx;
}

void puni::Material::setIntProperty(std::string prop, int val)
{
	shader->setInt(prop, val);
}

void puni::Material::setTransformProperty(std::string prop, glm::mat4 transform)
{
	if (shader)
	{
		unsigned int trLoc = glGetUniformLocation(shader->ID(), prop.c_str());
		glUniformMatrix4fv(trLoc, 1, GL_FALSE, glm::value_ptr(transform));
	}
}

void puni::Material::use()
{
	if (shader)
	{
		shader->use();
		if (texture)
			texture->use();
	}
}

const std::vector<puni::VertexAttributes> puni::Material::MaterialAttributes() const
{
	return attributes;
}

void puni::Material::createDefaultAttributes()
{
	VertexAttributes attrib[] = {
		{
			0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::pos))
		},
		{
			1, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::col))
		}
	};

	attributes.insert(attributes.begin(), attrib, attrib + 2);
}
