#include "Block.h"

namespace RaiderCraft
{
	void Block::setFaceTexture(BlockFace face, std::string textureName)
	{
		if (face != ALL || face != SIDES)
			_blockFaceTextures.insert(std::pair(face, textureName));
		else
		{
			if (face == ALL)
			{
				_blockFaceTextures.insert(std::pair(POSITIVE_Y, textureName));
				_blockFaceTextures.insert(std::pair(NEGATIVE_Y, textureName));
				_blockFaceTextures.insert(std::pair(NEGATIVE_X, textureName));
				_blockFaceTextures.insert(std::pair(POSITIVE_X, textureName));
				_blockFaceTextures.insert(std::pair(POSITIVE_Z, textureName));
				_blockFaceTextures.insert(std::pair(NEGATIVE_Z, textureName));
			}
			else if (face == SIDES)
			{
				_blockFaceTextures.insert(std::pair(NEGATIVE_X, textureName));
				_blockFaceTextures.insert(std::pair(POSITIVE_X, textureName));
				_blockFaceTextures.insert(std::pair(POSITIVE_Z, textureName));
				_blockFaceTextures.insert(std::pair(NEGATIVE_Z, textureName));
			}
		}
	}

	void Block::loadTextures(Raider::Texture::TextureArray textureArray)
	{
		for (const auto& entry : _blockFaceTextures)
		{
			auto iter = textureArray.textureEntries.find(entry.second);
			if (iter != textureArray.textureEntries.end())
			{
				_textureAtlasLayers[entry.first] = iter->second;
			}
		}
	}
}