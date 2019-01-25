#pragma once

#include <filesystem>
#include <Raider/GL.h>
#include <Raider/Core.h>

#include <stb_image.h>

namespace Raider
{
	class Texture
	{
	public:
		GLuint createTexture(const char* path)
		{
			GLuint texture;
			int width, height, nrChannels;
			unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);

			if (data)
			{
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

				stbi_image_free(data);
				return texture;
			}

			return -1;
		}

		struct TextureArray
		{
			GLuint textureID;
			std::unordered_map<std::string, uint8_t> textureEntries;
		};

		static TextureArray create2DTextureArray(const char* pathToTextureDIR, int texelWidth, int texelHeight, std::vector<std::string> fileNames)
		{
			GLuint textureID;

			glGenTextures(1, &textureID);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D_ARRAY, textureID);

			glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGBA8, texelWidth, texelHeight, fileNames.size());

			unsigned int z = 0;

			int fileWidth, fileHeight, nrChannels;

			TextureArray retVal;
			retVal.textureID = textureID;

			for (const auto& textureFile : fileNames)
			{
				unsigned char* data = stbi_load(textureFile.c_str(), &fileWidth, &fileHeight, &nrChannels, 0);
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, z, texelWidth, texelHeight, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
				std::string textureName = textureFile;
				textureName.replace(textureName.end() - 4, textureName.end(), "");
				retVal.textureEntries.insert(std::pair(textureName, z));
				stbi_image_free(data);
				z++;
			}

			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			return retVal;
		}
	};
}