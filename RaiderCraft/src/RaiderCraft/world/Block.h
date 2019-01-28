#pragma once

#include <cstdint>

#include <Raider.h>

namespace RaiderCraft
{
	struct BlockFaceLayers
	{
		int NX;
		int NY;
		int NZ;
		int PX;
		int PY;
		int PZ;
	};

	enum BlockFace
	{
		NX = 0,
		NY = 1,
		NZ = 2,
		PX = 3,
		PY = 4,
		PZ = 5,

		SIDES = 6,
		ALL = 7
	};

	struct BlockData
	{
		BlockFaceLayers textureLayers;
	};

	class Block
	{
	private:
		friend class BlockManager;
		int _blockID;
		const char* _name;
		BlockData _data;
	public:
		Block(const char * name, BlockData blockData);
		int getBlockID() const { return _blockID; }
		const char* getName() const { return _name; }
		BlockData& getBlockData() { return _data; }
	};

	class BlockManager
	{
	private:
		Raider::Texture::TextureArray _textureAtlas;
		std::vector<Block> _registeredBlocks;
	public:
		static BlockManager* getInstance();

		int registerBlock(Block block);
		Block getRegisteredBlock(int blockID);
		Block getRegisteredBlock(const char* blockName);
		int getLastRegisteredBlockID();

		void loadTextureAtlas(int texelWidth, int texelHeight, std::vector<std::string> fileNames);
		void setBlockTexture(Block& block, BlockFace face, const char* textureName);

		Raider::Texture::TextureArray getTextureAtlas() { return _textureAtlas; }
	};
}