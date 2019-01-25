#pragma once

#include <thread>
#include <Raider/RaiderTime.h>

#include "ChunkMesh.h"
#include "../world/World.h"
#include "ChunkMeshExtractor.h"

namespace RaiderCraft
{
	class ChunkMeshBuilder
	{
	private:
		ChunkMeshExtractor _meshExtractor;

		void uploadMesh(ChunkMesh& chunkMesh);
	public:
		ChunkMeshBuilder() {}

		void buildChunk(World* world, int chunkX, int chunkY, int chunkZ);
	};
}