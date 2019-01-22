#include "ChunkMeshExtractor.h"

namespace RaiderCraft
{
	VisibleBlockFaces ChunkMeshExtractor::checkForVisibleFaces(World* world, int blockX, int blockY, int blockZ)
	{
		VisibleBlockFaces visibleFaces;

		int currentBlock = world->getBlockAt(blockX, blockY, blockZ);
		int nxBlock = world->getBlockAt(blockX - 1, blockY, blockZ);
		int nyBlock = world->getBlockAt(blockX, blockY - 1, blockZ);
		int nzBlock = world->getBlockAt(blockX, blockY, blockZ - 1);
		int pxBlock = world->getBlockAt(blockX + 1, blockY, blockZ);
		int pyBlock = world->getBlockAt(blockX, blockY + 1, blockZ);
		int pzBlock = world->getBlockAt(blockX, blockY, blockZ + 1);

		visibleFaces.NX = nxBlock == 0;
		visibleFaces.NY = nyBlock == 0;
		visibleFaces.NZ = nzBlock == 0;
		visibleFaces.PX = pxBlock == 0;
		visibleFaces.PY = pyBlock == 0;
		visibleFaces.PZ = pzBlock == 0;
		
		return visibleFaces;
	}

	void ChunkMeshExtractor::createMeshData(World* world, int chunkX, int chunkY, int chunkZ)
	{
		Chunk* chunk = world->getChunkAt(chunkX, chunkY, chunkZ);
		ChunkMesh& chunkMesh = *(chunk->getChunkMesh());
		chunkMesh.getData().chunkRenderX = chunkX;
		chunkMesh.getData().chunkRenderY = chunkY;
		chunkMesh.getData().chunkRenderZ = chunkZ;
		std::vector<glm::vec4> chunkQuads;
		int _currentIndices[RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1];

		std::fill_n(&_currentIndices[0][0][0], std::pow(RD_CHUNK_DIM + 1, 3), -1);

		Raider::RaiderDebugTimer::RaiderDebugSection section("");

		for (int y = 0; y < RD_CHUNK_DIM; y++)
		{
			Chunk::ChunkLayer layer = chunk->getLayerAt(y);
			if (!layer.shouldDraw())
				continue;
			else if (layer.isAllSolid())
			{
				bool shouldContinue = false;
				if (y > 0 && y < 15)
				{
					if (chunk->getLayerAt(y + 1).isAllSolid() && chunk->getLayerAt(y - 1).isAllSolid())
						shouldContinue = true;
				}
				if (shouldContinue)
					continue;
			}
			for (int x = 0; x < RD_CHUNK_DIM; x++)
			{
				for (int z = 0; z < RD_CHUNK_DIM; z++)
				{
					if (chunk->getBlockAt(x, y, z) != 0)
					{
						float r = y / 30.f;
						float g = y / 80.f;
						float b = y / 100.f;

						VisibleBlockFaces visibleFaces = checkForVisibleFaces(world, x + (chunkX * RD_CHUNK_DIM), y + (chunkY * RD_CHUNK_DIM), z + (chunkZ * RD_CHUNK_DIM));

						if (visibleFaces.NX)
						{
							int v0 = addVertex(x, y, z, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.NZ)
						{
							int v0 = addVertex(x, y, z, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y, z, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.NY)
						{
							int v0 = addVertex(x, y, z, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y, z, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PX)
						{
							int v0 = addVertex(x + 1, y, z, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PZ)
						{
							int v0 = addVertex(x, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y, z + 1, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PY)
						{
							int v0 = addVertex(x, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y + 1, z, r, g, b, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y + 1, z + 1, r, g, b, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
					}
				}
			}
		}

		for (auto quad : chunkQuads)
		{
			int size = chunkMesh.getNumOfVertices();
			RD_ASSERT(quad.x < size && quad.y < size && quad.z < size && quad.w < size, "Quad has invalid indices.")
			chunkMesh.addQuad(quad.x, quad.y, quad.z, quad.w);
		}
	}
}