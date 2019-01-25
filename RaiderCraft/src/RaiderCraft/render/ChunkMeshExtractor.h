#pragma once

#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <Raider/RaiderTime.h>

#include "ChunkMesh.h"
#include "../world/World.h"
#include "../world/Block.h"

namespace RaiderCraft
{
	struct VisibleBlockFaces
	{
		bool NX = false;
		bool NY = false;
		bool NZ = false;
		bool PX = false;
		bool PY = false;
		bool PZ = false;
	};

	class ChunkMeshExtractor
	{
	public:
		struct ChunkIndex
		{
			ChunkIndex(int _index, float _tx, float _ty, float _tw) : index(_index), tx(_tx), ty(_ty), tw(_tw) {}

			int index = -1;

			float tx;
			float ty;
			float tw;
		};
	private:
		VisibleBlockFaces checkForVisibleFaces(World* world, int blockX, int blockY, int blockZ);
		int addVertex(int x, int y, int z, float tx, float ty, float tw, ChunkMesh& mesh, std::vector<ChunkIndex>(&indices)[RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1]);
	public:
		void createMeshData(World* world, int chunkX, int chunkY, int chunkZ);
	};
}