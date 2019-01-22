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
		Raider::RaiderDebugTimer _debugTimer;

		void uploadMesh(ChunkMesh& chunkMesh);
	public:
		ChunkMeshBuilder() : _debugTimer("ChunkMeshBuilder") {}

		void buildChunk(World* world, int chunkX, int chunkY, int chunkZ);
	};
}