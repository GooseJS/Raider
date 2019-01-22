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

		int chunkRenderX = 0;
		int chunkRenderY = 0;
		int chunkRenderZ = 0;

		bool init = false;
		bool needsRebuild = false;
	};

	struct ChunkVertex
	{
		float xyz[3];
		float rgb[3];

		//ChunkVertex(float _x, float _y, float _z, float _r, float _g, float _b) : x(_x), y(_y), z(_z), r(_r), g(_g), b(_b) {}
		ChunkVertex(float _x, float _y, float _z, float _r, float _g, float _b)
		{
			xyz[0] = _x;
			xyz[1] = _y;
			xyz[2] = _z;
			rgb[0] = _r;
			rgb[1] = _g;
			rgb[2] = _b;
		}
	};

	class ChunkMesh
	{
	private:
		ChunkMeshData _chunkMeshData{};
		std::vector<int> _chunkIndices;
		std::vector<ChunkVertex> _chunkVertices;
	public:
		inline int addVertex(float x, float y, float z, float r, float g, float b)
		{
			_chunkVertices.emplace_back(x, y, z, r, g, b);
			return _chunkVertices.size() - 1;
		}

		inline void addTriangle(int i0, int i1, int i2)
		{
			_chunkIndices.push_back(i0);
			_chunkIndices.push_back(i1);
			_chunkIndices.push_back(i2);
		}

		inline void addQuad(int i0, int i1, int i2, int i3)
		{
			addTriangle(i0, i1, i2);
			addTriangle(i0, i2, i3);
		}

		inline void clearTempMeshData()
		{
			_chunkVertices.clear();
			_chunkIndices.clear();
		}

		ChunkMeshData& getData() { return _chunkMeshData; }
		int getNumOfVertices() { return _chunkVertices.size(); }
		int getNumOfIndices() { return _chunkIndices.size(); }

		void* getRawVertexData() { return &_chunkVertices[0]; }
		ChunkVertex* getChunkVertex() { return &_chunkVertices[0]; }
		int* getRawIndexData() { return &_chunkIndices[0]; }
	};
}