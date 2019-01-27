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

		for (int y = 0; y < RD_CHUNK_DIM; y++)
		{
			Chunk::ChunkLayer layer = chunk->getLayerAt(y);

			if (!layer.shouldDraw())
				continue;
			else if (layer.isAllSolid())
			{
				if (y > 0 && y < 15)
				{
					if (chunk->getLayerAt(y + 1).isAllSolid() && chunk->getLayerAt(y - 1).isAllSolid()) // TODO: This needs to be checking other chunk layers, above, below, and to the sides
						continue;
				}
			}

			for (int x = 0; x < RD_CHUNK_DIM; x++)
			{
				for (int z = 0; z < RD_CHUNK_DIM; z++)
				{
					Block currentBlock = BlockManager::getInstance()->getRegisteredBlock(chunk->getBlockAt(x, y, z));
					if (currentBlock.getBlockID() != 0) // TODO: This should really actually be checking if the block should be drawn like a block
					{
						VisibleBlockFaces visibleFaces = checkForVisibleFaces(world, x + (chunkX * RD_CHUNK_DIM), y + (chunkY * RD_CHUNK_DIM), z + (chunkZ * RD_CHUNK_DIM));

						BlockData& blockData = currentBlock.getBlockData();
						static float tex[2] = { 0.0f, 1.0f };
						if (visibleFaces.NX)
						{
							int layer = blockData.textureLayers.NX;
							int v0 = chunkMesh.addVertex(x, y, z  + 1, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x, y, z, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x, y + 1, z + 1, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x, y + 1, z, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
						if (visibleFaces.NZ)
						{
							int layer = blockData.textureLayers.NZ;
							int v0 = chunkMesh.addVertex(x, y, z, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x + 1, y, z, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x, y + 1, z, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x + 1, y + 1, z, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
						if (visibleFaces.NY)
						{
							int layer = blockData.textureLayers.NY;
							int v0 = chunkMesh.addVertex(x, y, z + 1, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x + 1, y, z + 1, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x, y, z, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x + 1, y, z, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
						if (visibleFaces.PX)
						{
							int layer = blockData.textureLayers.PX;
							int v0 = chunkMesh.addVertex(x + 1, y, z, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x + 1, y, z + 1, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x + 1, y + 1, z, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x + 1, y + 1, z + 1, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
						if (visibleFaces.PZ)
						{
							int layer = blockData.textureLayers.PZ;
							int v0 = chunkMesh.addVertex(x + 1, y, z + 1, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x, y, z + 1, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x + 1, y + 1, z + 1, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x, y + 1, z + 1, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
						if (visibleFaces.PY)
						{
							int layer = blockData.textureLayers.PY;
							int v0 = chunkMesh.addVertex(x, y + 1, z, tex[0], tex[0], layer);
							int v1 = chunkMesh.addVertex(x + 1, y + 1, z, tex[1], tex[0], layer);
							int v2 = chunkMesh.addVertex(x, y + 1, z + 1, tex[0], tex[1], layer);
							int v3 = chunkMesh.addVertex(x + 1, y + 1, z + 1, tex[1], tex[1], layer);
							chunkMesh.addQuad(v0, v1, v2, v3);
						}
					}
				}
			}
		}
	}
}