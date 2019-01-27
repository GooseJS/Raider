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
	private:
		VisibleBlockFaces checkForVisibleFaces(World* world, int blockX, int blockY, int blockZ);
	public:
		void createMeshData(World* world, int chunkX, int chunkY, int chunkZ);
	};
}