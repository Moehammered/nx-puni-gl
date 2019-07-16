#include "Texture.h"
#include "stb_image.h"
#include <glad\glad.h>

puni::Texture::Texture()
{
	maxActiveTextures = GL_TEXTURE31 - GL_TEXTURE0;
	textureID = 0;
}

puni::Texture::Texture(std::string path)
{
	maxActiveTextures = GL_TEXTURE31 - GL_TEXTURE0;
	textureID = 0;
	loadTexture(path);
}


puni::Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}

const int puni::Texture::Width()
{
	return width;
}

const int puni::Texture::Height()
{
	return height;
}

const int puni::Texture::ChannelCount()
{
	return channelCount;
}

const unsigned int puni::Texture::ID()
{
	return textureID;
}

void puni::Texture::loadTexture(std::string const& path)
{
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channelCount, 0);

	if (data)
	{
		destroyTexture();
		glGenTextures(1, &textureID);
		glActiveTexture(GL_TEXTURE0);
		use();
		//configure
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//upload texture data
		GLuint imageFormat = channelCount == 4 ? GL_RGBA : GL_RGB;		
		glTexImage2D(GL_TEXTURE_2D, 0, imageFormat, width, height, 
			0, imageFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0); //unbind, finished config

		stbi_image_free(data);
	}
	else
	{
		printf("Error loading texture: %s\n\n", path.c_str());
	}
}

void puni::Texture::use()
{
	glBindTexture(GL_TEXTURE_2D, textureID);
}

void puni::Texture::use(unsigned char textureNumber)
{
	textureNumber = textureNumber > maxActiveTextures ? 
		maxActiveTextures : textureNumber;

	glActiveTexture(GL_TEXTURE0 + textureNumber);
	use();
}

void puni::Texture::destroyTexture()
{
	if(textureID)
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
}