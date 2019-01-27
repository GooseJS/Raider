#pragma once

#define RD_CHUNK_DIM			16
#define RD_CHUNK_COLUMN_HEIGHT	16

#include <memory>
#include <cstdint>
#include <Raider/Logger.h>

#include "../render/ChunkMesh.h"

namespace RaiderCraft
{
	class ChunkData
	{
	private:
		int* _data;
	public:
		ChunkData(int dataSize)
		{
			_data = new int[dataSize] {};
		}
		~ChunkData() { delete[] _data; }

		const int getDataAt(int index) const { return _data[index]; }
		void setDataAt(int index, int data) { _data[index] = data; }
	};

	struct ChunkPos
	{
		union
		{
			struct
			{
				uint16_t padding;
				uint8_t positiveXZ; // TODO: See if there is a better way to store postive XY
				uint8_t y;
				uint16_t x;
				uint16_t z;
			};
			uint64_t totalValue;
		};

		ChunkPos(uint64_t _totalValue) : totalValue(_totalValue) {}
		ChunkPos(int _x, int _y, int _z)
		{
			if (_x > 0 && _z > 0) positiveXZ= 3;
			else if (_x > 0) positiveXZ = 1;
			else if (_z > 0) positiveXZ = 2;
			else positiveXZ = 0;
			x = std::abs(_x);
			y = std::abs(_y);
			z = std::abs(_z);
			padding = 0;
		}

		const bool& hasPositiveX()
		{
			return (positiveXZ & 1);
		}

		const bool& hasPositiveZ()
		{
			return (positiveXZ & 2);
		}
	};

	class Chunk
	{
	public:
		struct ChunkLayer
		{
		private:
			int _solidBlockCount = 0;
		public:
			void update(int block)
			{
				if (block != 0) // TODO: This should be checking for block transparency
					_solidBlockCount++;
				else
					_solidBlockCount--;
			}

			bool isAllSolid() const
			{
				return _solidBlockCount == RD_CHUNK_DIM * RD_CHUNK_DIM;
			}

			bool shouldDraw() const
			{
				return _solidBlockCount != 0;
			}
		};
		struct SurroundingChunks
		{
			Chunk* NX;
			Chunk* NY;
			Chunk* NZ;
			Chunk* PX;
			Chunk* PY;
			Chunk* PZ;
		};
	private:
		ChunkPos _pos;
		ChunkData _data;
		ChunkMesh _chunkMesh;
		ChunkLayer _chunkLayers[RD_CHUNK_DIM];
		SurroundingChunks _surroundingChunks;

		inline int blockToChunkIndex(int x, int y, int z)
		{
			return x | y << 4 | z << 8;
		}
	public:
		Chunk(int x, int y, int z) : _pos(x, y, z), _data(RD_CHUNK_DIM * RD_CHUNK_DIM * RD_CHUNK_DIM) {}

		inline int getBlockAt(int x, int y, int z)
		{
			RD_ASSERT(x >= 0 && x < RD_CHUNK_DIM && y >= 0 && y < RD_CHUNK_DIM && z >= 0 && z < RD_CHUNK_DIM, "Block out of bounds");
			return getBlockAt(blockToChunkIndex(x, y, z));
		}
		inline int getBlockAt(int index) { return _data.getDataAt(index); }

		void setBlockAt(int x, int y, int z, int data)
		{
			RD_ASSERT(x >= 0 && x < RD_CHUNK_DIM && y >= 0 && y < RD_CHUNK_DIM && z >= 0 && z < RD_CHUNK_DIM, "Block out of bounds");
			setBlockAt(blockToChunkIndex(x, y, z), data);
			_chunkLayers[y].update(data);
		}

		void setBlockAt(int index, int data)
		{
			_data.setDataAt(index, data);
		}

		ChunkLayer getLayerAt(int y)
		{
			RD_ASSERT(y < RD_CHUNK_DIM, "Layer out of bounds");
			return _chunkLayers[y];
		}

		ChunkMesh* getChunkMesh() { return &_chunkMesh; }
		SurroundingChunks* getSurroundingChunks() { return &_surroundingChunks; }

		ChunkPos getChunkPos() { return _pos; }
	};
}