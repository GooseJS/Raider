#include "ChunkMeshBuilder.h"

namespace RaiderCraft
{
	void ChunkMeshBuilder::uploadMesh(ChunkMesh& chunkMesh)
	{
		ChunkMeshData& meshData = chunkMesh.getData();
		if (!meshData.init)
			glGenVertexArrays(1, &(meshData.chunkVAO));
		glBindVertexArray(meshData.chunkVAO);

		if (!meshData.init)
		{
			glGenBuffers(1, &(meshData.chunkVertexBuffer));
			glGenBuffers(1, &(meshData.chunkIndexBuffer));
		}
		void* lmao = chunkMesh.getRawVertexData();
		ChunkVertex* lmao2 = chunkMesh.getChunkVertex();

		glBindBuffer(GL_ARRAY_BUFFER, meshData.chunkVertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, chunkMesh.getNumOfVertices() * sizeof(ChunkVertex), chunkMesh.getRawVertexData(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshData.chunkIndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, chunkMesh.getNumOfIndices() * sizeof(int), chunkMesh.getRawIndexData(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(ChunkVertex), (GLvoid*)offsetof(ChunkVertex, xyz));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(ChunkVertex), (GLvoid*)(offsetof(ChunkVertex, rgb)));

		meshData.numOfIndices = chunkMesh.getNumOfIndices();
		meshData.numOfVertices = chunkMesh.getNumOfVertices();

		chunkMesh.clearTempMeshData();

		meshData.init = true;
	}

	void ChunkMeshBuilder::buildChunk(World* world, int chunkX, int chunkY, int chunkZ)
	{
		_meshExtractor.createMeshData(world, chunkX, chunkY, chunkZ);
		ChunkMesh& chunkMesh = *world->getChunkAt(chunkX, chunkY, chunkZ)->getChunkMesh();
		uploadMesh(chunkMesh); // Tested on latest version. Takes <1ms to run
	}
}