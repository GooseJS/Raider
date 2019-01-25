#pragma once

#include <map>

#include "Chunk.h"

namespace RaiderCraft
{
	class ChunkProvider
	{
	private:
		std::unordered_map<uint64_t, Chunk*> _chunks;

		uint64_t chunkPosToChunkIndex(int chunkX, int chunkY, int chunkZ)
		{
			ChunkPos chunkPos(chunkX, chunkY, chunkZ);
			return chunkPos.totalValue;
		}
	public:
		ChunkProvider() {}
		~ChunkProvider()
		{
			for (auto iter = _chunks.begin(); iter != _chunks.end(); iter++)
			{
				Chunk* chunk = _chunks.at(iter->first);
				delete chunk;
			}
		}

		Chunk* getChunkAt(int chunkX, int chunkY, int chunkZ)
		{
			auto chunkIter = _chunks.find(chunkPosToChunkIndex(chunkX, chunkY, chunkZ));
			Chunk* chunk;
			if (chunkIter == _chunks.end())
			{
				chunk = new Chunk(chunkX, chunkY, chunkZ);
				_chunks.insert(std::pair<uint64_t, Chunk*>(chunkPosToChunkIndex(chunkX, chunkY, chunkZ), chunk));
			}
			else
			{
				chunk = chunkIter->second;
			}
			return chunk;
		}

		std::vector<Chunk*> getLoadedChunks()
		{
			std::vector<Chunk*> loadedChunks;
			for (auto &chunk : _chunks)
			{
				loadedChunks.push_back(chunk.second);
			}
			return loadedChunks;
		}
	};

	class World
	{
	private:
		ChunkProvider _chunkProvider;

		int chunkPos(int blockPos) { return blockPos & RD_CHUNK_DIM - 1; }
	public:
		template <bool blockPos = false>
		Chunk* getChunkAt(int x, int y, int z)
		{
			if (blockPos)
				return _chunkProvider.getChunkAt(x >> 4, y >> 4, z >> 4);
			return _chunkProvider.getChunkAt(x, y, z);
		}

		int getBlockAt(int blockX, int blockY, int blockZ)
		{
			return getChunkAt<true>(blockX, blockY, blockZ)->getBlockAt(chunkPos(blockX), chunkPos(blockY), chunkPos(blockZ));
		}

		void setBlockAt(int blockX, int blockY, int blockZ, int block)
		{
			getChunkAt<true>(blockX, blockY, blockZ)->setBlockAt(chunkPos(blockX), chunkPos(blockY), chunkPos(blockZ), block);
		}

		inline std::vector<Chunk*> getLoadedChunks()
		{
			return _chunkProvider.getLoadedChunks();
		}
	};
}