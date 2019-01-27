#include "Block.h"

namespace RaiderCraft
{
	///region Block
	Block::Block(const char * name, BlockData blockData) : _blockID(BlockManager::getInstance()->getLastRegisteredBlockID()), _name(name), _data(blockData)
	{

	}
	///endregion

	///region BlockManager
	BlockManager* BlockManager::getInstance()
	{
		static BlockManager instance;
		return &instance;
	}

	int BlockManager::registerBlock(Block block)
	{
		_registeredBlocks.push_back(block);
		return _registeredBlocks.size() - 1;
	}

	Block BlockManager::getRegisteredBlock(int blockID)
	{
		return _registeredBlocks[blockID];
	}

	Block BlockManager::getRegisteredBlock(const char * blockName)
	{
		for (const auto& block : _registeredBlocks)
		{
			if (block.getName() == blockName)
				return block;
		}
	}

	int BlockManager::getLastRegisteredBlockID()
	{
		return _registeredBlocks.size() - 1;
	}

	void BlockManager::loadTextureAtlas(const char* path, int texelWidth, int texelHeight, std::vector<std::string> fileNames)
	{
		_textureAtlas = Raider::Texture::create2DTextureArray(path, texelWidth, texelHeight, fileNames);
	}

	void BlockManager::setBlockTexture(Block & block, BlockFaceLayers layer, const char * textureName)
	{
		if (layer)
	}
	///endregion
}
