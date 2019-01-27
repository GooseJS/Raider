#include "ChunkMesh.h"

namespace RaiderCraft
{
	int ChunkMesh::addVertex(float x, float y, float z, float tx, float ty, float tw)
	{
		_chunkVertices.emplace_back(x, y, z, tx, ty, tw);
		return static_cast<int>(_chunkVertices.size()) - 1;
	}

	void ChunkMesh::addTriangle(int i0, int i1, int i2)
	{
		_chunkIndices.push_back(i0);
		_chunkIndices.push_back(i1);
		_chunkIndices.push_back(i2);
	}

	// STARTING i0 FROM LOWER LEFT CORNER GOING CCW
	void ChunkMesh::addQuad(int i0, int i1, int i2, int i3)
	{
		addTriangle(i0, i1, i2);
		addTriangle(i3, i2, i1);
	}

	void ChunkMesh::clearTempMeshData()
	{
		_chunkVertices.clear();
		_chunkVertices.resize(0);
		_chunkIndices.clear();
		_chunkIndices.resize(0);
	}
}