#pragma once

#include <noise/noise.h>
#include <noiseutils.h>

#include "World.h"

namespace RaiderCraft
{
	class WorldGenerator
	{
	private:
		noise::module::Perlin _perlin;
		noise::utils::NoiseMap _heightMap;
		noise::utils::NoiseMapBuilderPlane _heightMapBuilder;

	public:
		void generateWorld(World* world)
		{
			_heightMapBuilder.SetSourceModule(_perlin);
			_heightMapBuilder.SetDestNoiseMap(_heightMap);
			_heightMapBuilder.SetDestSize(256, 256);
			_heightMapBuilder.SetBounds(0.0, 0.5, 0.0, 0.5);
			_heightMapBuilder.Build();
			for (int x = 0; x < 256; x++)
			{
				for (int z = 0; z < 256; z++)
				{
					int maxY = (64.f * _heightMap.GetValue(x, z));
					for (int y = 0; y < maxY; y++)
					{
						world->setBlockAt(x, y, z, 2);
						if (world->getBlockAt(x, y - 1, z) == 2)
							world->setBlockAt(x, y - 1, z, 1);
					}
				}
			}
		}
	};
}