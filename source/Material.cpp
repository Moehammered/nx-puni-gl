#include "Material.h"

#include <glad\glad.h>
#include <glm\gtc\type_ptr.hpp>
#include "Vertex.h"

puni::Material::Material()
{
	//shader = new Shader("transform-coltex-shader.vs", "coltex-shader.fs");
    texture = 0;
    shader = 0;
	createDefaultAttributes();
}

puni::Material::Material(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    texture = 0;
    shader = 0;
	loadShader(vertexShaderPath, fragmentShaderPath);
	createDefaultAttributes();
}

puni::Material::Material(Shader * const preMadeShader)
{
    texture = 0;
	shader = preMadeShader;
	createDefaultAttributes();
}


puni::Material::~Material()
{
	// printf("Destroying Material.\n\n");
	// printf("Deleting Shader in Material.\n\n");
	delete shader;
	// printf("Deleting Texture in Material.\n\n");
	delete texture;
	// printf("Destroyed Material.\n\n");
}

unsigned int puni::Material::shaderID()
{
	return shader->ID();
}

void puni::Material::loadShader(std::string vertP, std::string fragP)
{
	if(shader)
	{
		delete shader;
		shader = 0;
	}
	shader = new Shader();
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
