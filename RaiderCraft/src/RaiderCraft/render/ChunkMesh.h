#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <Raider/GL.h>

namespace RaiderCraft
{
	struct ChunkMeshData
	{
		GLuint chunkVAO = 0;
		GLuint chunkVertexBuffer = 0;
		GLuint chunkIndexBuffer = 0;

		int numOfVertices = 0;
		int numOfIndices = 0;

		bool init = false;
		bool needsRebuild = false;
	};

	struct ChunkVertex
	{
		float xyz[3];
		float texCoord[3];
		
		ChunkVertex() {}

		ChunkVertex(float _x, float _y, float _z, float _tx, float _ty, float _tw)
		{
			xyz[0] = _x;
			xyz[1] = _y;
			xyz[2] = _z;
			texCoord[0] = _tx;
			texCoord[1] = _ty;
			texCoord[2] = _tw;
		}
	};

	class ChunkMesh
	{
	private:
		ChunkMeshData _chunkMeshData{};
		std::vector<int> _chunkIndices;
		std::vector<ChunkVertex> _chunkVertices;
	public:
		int addVertex(float x, float y, float z, float tx, float ty, float tw);
		void addTriangle(int i0, int i1, int i2);
		void addQuad(int i0, int i1, int i2, int i3);
		void clearTempMeshData();

		ChunkMeshData& getData() { return _chunkMeshData; }
		int getNumOfVertices() { if (_chunkVertices.size() != 0) return static_cast<int>(_chunkVertices.size()); else return _chunkMeshData.numOfVertices; }
		int getNumOfIndices() { if (_chunkIndices.size() != 0) return static_cast<int>(_chunkIndices.size()); else return _chunkMeshData.numOfIndices; }

		void* getRawVertexData() { return &_chunkVertices[0]; }
		ChunkVertex* getChunkVertex() { return &_chunkVertices[0]; }
		int* getRawIndexData() { return &_chunkIndices[0]; }
	};
}