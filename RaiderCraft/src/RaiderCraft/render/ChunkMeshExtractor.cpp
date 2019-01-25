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

	int ChunkMeshExtractor::addVertex(int x, int y, int z, float tx, float ty, float tw, ChunkMesh & mesh, std::vector<ChunkIndex>(&indices)[RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1])
	{
		std::vector<ChunkIndex> result = indices[x][y][z];
		if (result.empty())
		{
			int index = mesh.addVertex(x, y, z, tx, ty, tw);
			indices[x][y][z].emplace_back(index, tx, ty, tw);
			return index;
		}

		for (auto& index : result)
		{
			if (index.tx == tx && index.ty == ty && index.tw == tw)
				return index.index;
		}

		int index = mesh.addVertex(x, y, z, tx, ty, tw);
		indices[x][y][z].emplace_back(index, tx, ty, tw);
		return index;
	}

	void ChunkMeshExtractor::createMeshData(World* world, int chunkX, int chunkY, int chunkZ)
	{
		Chunk* chunk = world->getChunkAt(chunkX, chunkY, chunkZ);
		ChunkMesh& chunkMesh = *(chunk->getChunkMesh());

		std::vector<glm::vec4> chunkQuads;
		std::vector<ChunkMeshExtractor::ChunkIndex> _currentIndices[RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1][RD_CHUNK_DIM + 1];

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
					Block currentBlock = Blocks::getInstance()->getBlock(chunk->getBlockAt(x, y, z));
					if (currentBlock.getBlockID() != 0) // TODO: This should really actually be checking if the block should be drawn like a block
					{
						VisibleBlockFaces visibleFaces = checkForVisibleFaces(world, x + (chunkX * RD_CHUNK_DIM), y + (chunkY * RD_CHUNK_DIM), z + (chunkZ * RD_CHUNK_DIM));

						static float tex[2] = { 0.0f, 1.0f };
						if (visibleFaces.NX)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::NEGATIVE_X);
							int v0 = addVertex(x, y, z, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y + 1, z, tex[0], tex[0], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x, y + 1, z + 1, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y, z + 1, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.NZ)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::NEGATIVE_Z);
							int v0 = addVertex(x, y, z, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y, z, tex[1], tex[1], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y + 1, z, tex[0], tex[0], layer, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.NY)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::NEGATIVE_Y);
							int v0 = addVertex(x, y, z, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y, z + 1, tex[0], tex[0], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y, z + 1, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y, z, tex[1], tex[1], layer, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PX)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::POSITIVE_X);
							int v0 = addVertex(x + 1, y, z, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y, z + 1, tex[1], tex[1], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y + 1, z, tex[0], tex[0], layer, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PZ)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::POSITIVE_Z);
							int v0 = addVertex(x, y, z + 1, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x, y + 1, z + 1, tex[0], tex[0], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x + 1, y, z + 1, tex[1], tex[1], layer, chunkMesh, _currentIndices);
							chunkQuads.emplace_back(v0, v1, v2, v3);
						}
						if (visibleFaces.PY)
						{
							int layer = currentBlock.getTextureLayerForFace(Block::BlockFace::POSITIVE_Y);
							int v0 = addVertex(x, y + 1, z, tex[0], tex[1], layer, chunkMesh, _currentIndices);
							int v1 = addVertex(x + 1, y + 1, z, tex[1], tex[1], layer, chunkMesh, _currentIndices);
							int v2 = addVertex(x + 1, y + 1, z + 1, tex[1], tex[0], layer, chunkMesh, _currentIndices);
							int v3 = addVertex(x, y + 1, z + 1, tex[0], tex[0], layer, chunkMesh, _currentIndices);
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