#pragma once

#include <list>
#include <vector>
#include <glm/glm.hpp>
#include <Raider/RaiderTime.h>

#include "ChunkMesh.h"
#include "../world/World.h"

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
	private:
		VisibleBlockFaces checkForVisibleFaces(World* world, int blockX, int blockY, int blockZ);

		inline int addVertex(int x, int y, int z, float r, float g, float b, ChunkMesh& mesh, int (&indices)[RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1])
		{
			int result = indices[x][y][z];
			if (result == -1)
			{
				result = mesh.addVertex(x, y, z, r, g, b);
				indices[x][y][z] = result;
				return result;
			}
			return result;
		}
	public:
		void createMeshData(World* world, int chunkX, int chunkY, int chunkZ);
	};
}