#ifndef SWITCH__TEXTURE__H_
#define SWITCH__TEXTURE__H_

#include <string>

namespace puni
{
	class Texture
	{
		public:
			Texture();
			Texture(std::string path);
			~Texture();

			const int Width();
			const int Height();
			const int ChannelCount();
			const unsigned int ID();

			void loadTexture(std::string const& path);
			void use();
			void use(unsigned char textureNumber);

		private:
			int width, height, channelCount;
			unsigned char maxActiveTextures;
			unsigned int textureID;

			void destroyTexture();
	};
}

#endif