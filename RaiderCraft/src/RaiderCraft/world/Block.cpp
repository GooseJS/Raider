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
		int blockID = _registeredBlocks.size();
		block._blockID = blockID;
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

	void BlockManager::loadTextureAtlas(int texelWidth, int texelHeight, std::vector<std::string> fileNames)
	{
		_textureAtlas = Raider::Texture::create2DTextureArray(texelWidth, texelHeight, fileNames);
	}

	void BlockManager::setBlockTexture(Block& block, BlockFace face, const char* textureName)
	{
		if (face != ALL && face != SIDES)
		{
			switch (face)
			{
				case NX:
					block.getBlockData().textureLayers.NX = _textureAtlas.getEntry(textureName);
					break;
				case NY:
					block.getBlockData().textureLayers.NY = _textureAtlas.getEntry(textureName);
					break;
				case NZ:
					block.getBlockData().textureLayers.NZ = _textureAtlas.getEntry(textureName);
					break;
				case PX:
					block.getBlockData().textureLayers.PX = _textureAtlas.getEntry(textureName);
					break;
				case PY:
					block.getBlockData().textureLayers.PY = _textureAtlas.getEntry(textureName);
					break;
				case PZ:
					block.getBlockData().textureLayers.PZ = _textureAtlas.getEntry(textureName);
					break;
			}
		}
		else if (face == ALL)
		{
			block.getBlockData().textureLayers.NX = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.NY = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.NZ = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.PX = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.PY = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.PZ = _textureAtlas.getEntry(textureName);
		}
		else if (face == SIDES)
		{
			block.getBlockData().textureLayers.NX = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.NZ = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.PX = _textureAtlas.getEntry(textureName);
			block.getBlockData().textureLayers.PZ = _textureAtlas.getEntry(textureName);
		}
	}
	///endregion
}
