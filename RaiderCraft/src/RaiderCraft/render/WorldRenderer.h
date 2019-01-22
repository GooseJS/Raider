#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include <Raider/GL.h>
#include <glm/gtx/transform.hpp>
#include <Raider/render/shader.h>

#include "Camera.h"
#include "../world/World.h"

namespace RaiderCraft
{
	class WorldRenderer
	{
	private:
		Raider::Shader _shader;
		Camera* _worldRenderCam;
	public:
		WorldRenderer() {}
		void initRenderer()
		{
			_shader.initFromFile("shader.vert", "shader.frag");
		}

		void render(World* gameWorld)
		{
			glEnable(GL_DEPTH_TEST);
			//glEnable(GL_CULL_FACE);
			glFrontFace(GL_CW);
			_worldRenderCam->generateMatrices();
			glm::mat4 transformedMatrix = _worldRenderCam->getProjectionMatrix() * _worldRenderCam->getViewMatrix();

			_shader.use();

			glUniformMatrix4fv(_shader.uniform("projectionViewMatrix"), 1, GL_FALSE, &transformedMatrix[0][0]);
			glUniform3f(_shader.uniform("lightPos"), 0.0f, 64.f, 0.0f);

			glm::mat4 translation(1.0f);

			for (auto &chunk : gameWorld->getLoadedChunks())
			{
				if (chunk->getChunkMesh()->getData().init)
				{
					translation = glm::translate(glm::vec3(chunk->getChunkMesh()->getData().chunkRenderX * RD_CHUNK_DIM, chunk->getChunkMesh()->getData().chunkRenderY * RD_CHUNK_DIM, chunk->getChunkMesh()->getData().chunkRenderZ * RD_CHUNK_DIM));
					glUniformMatrix4fv(_shader.uniform("translationMatrix"), 1, GL_FALSE, &translation[0][0]);
					glBindVertexArray(chunk->getChunkMesh()->getData().chunkVAO);
					glDrawElements(GL_TRIANGLES, chunk->getChunkMesh()->getData().numOfIndices, GL_UNSIGNED_INT, nullptr);
				}
			}
		}

		void setWorldRenderCam(Camera* camera)
		{
			_worldRenderCam = camera;
		}
	};
}