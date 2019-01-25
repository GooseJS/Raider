#pragma once

#include <cstdint>

#include <Raider.h>

namespace RaiderCraft
{
	class Block
	{
	public:
		enum BlockFace
		{
			POSITIVE_Y = 0,
			NEGATIVE_Y = 1,
			NEGATIVE_X = 2,
			POSITIVE_X = 3,
			POSITIVE_Z = 4,
			NEGATIVE_Z = 5,

			SIDES = 6,
			ALL = 7
		};
	private:
		int _blockID;
		const char* _name; // TODO: Localization
		uint8_t _textureAtlasLayers[6];
		std::unordered_map<BlockFace, std::string> _blockFaceTextures;
	public:
		Block(int blockID, const char* name) : _blockID(blockID), _name(name) {}

		void setFaceTexture(BlockFace face, std::string textureName);

		uint8_t getTextureLayerForFace(BlockFace face) { return _textureAtlasLayers[face]; }
		void loadTextures(Raider::Texture::TextureArray textureArray);

		const int getBlockID() { return _blockID; }
		const char* getName() { return _name; }
	};

	class Blocks
	{
	private:
		std::vector<Block> _registeredBlocks;
		Blocks() {}
	public:
		static Blocks* getInstance() { static Blocks instance; return &instance; }

		void addBlock(Block block)
		{
			_registeredBlocks.push_back(block);
		}

		Block getBlock(int blockID)
		{
			return _registeredBlocks[blockID];
		}

		void loadBlockTextures(Raider::Texture::TextureArray textureArray)
		{
			for (auto& block : _registeredBlocks)
			{
				block.loadTextures(textureArray);
			}
		}
	};
}