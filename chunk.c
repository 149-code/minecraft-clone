#include "chunk.h"
#include "renderer.h"
#include <cglm/struct.h>

int getBlockIndex(int x, int y, int z)
{
	return x * CHUNK_Y * CHUNK_Z + y * CHUNK_Z + z;
}

bool isTransparent(int blockType)
{
	if (blockType == BLOCK_TYPE_AIR)
		return true;
	else
		return false;
}

void computeVisableFaces(Chunk* c)
{
	for (int x = 0; x < CHUNK_X; x++)
		for (int y = 0; y < CHUNK_Y; y++)
			for (int z = 0; z < CHUNK_Z; z++)
			{
				int index = getBlockIndex(x, y, z);

				if (c->blocks[index].blockType == BLOCK_TYPE_AIR)
					continue;

				u8 visibleFaces = 0;

				if (x == 0 ||
					isTransparent(
						c->blocks[getBlockIndex(x - 1, y, z)].blockType))
				{
					visibleFaces = visibleFaces | (1 << X_MINUS);
				}
				if (x == CHUNK_X - 1 ||
					isTransparent(
						c->blocks[getBlockIndex(x + 1, y, z)].blockType))
				{
					visibleFaces = visibleFaces | (1 << X_PLUS);
				}
				if (y == 0 ||
					isTransparent(
						c->blocks[getBlockIndex(x, y - 1, z)].blockType))
				{
					visibleFaces = visibleFaces | (1 << Y_MINUS);
				}
				if (y == CHUNK_Y - 1 ||
					isTransparent(
						c->blocks[getBlockIndex(x, y + 1, z)].blockType))
				{
					visibleFaces = visibleFaces | (1 << Y_PLUS);
				}
				if (z == 0 ||
					isTransparent(
						c->blocks[getBlockIndex(x, y, z - 1)].blockType))
				{
					visibleFaces = visibleFaces | (1 << Z_MINUS);
				}
				if (z == CHUNK_Z - 1 ||
					isTransparent(
						c->blocks[getBlockIndex(x, y, z + 1)].blockType))
				{
					visibleFaces = visibleFaces | (1 << Z_PLUS);
				}

				c->blocks[index].faceBitMask = visibleFaces;
			}
}

Chunk generateRandomChunk(vec3s pos, fnl_state noiseConfig)
{
	Chunk ret = {
		.pos = pos,
		.blocks = malloc(sizeof(Block) * CHUNK_X * CHUNK_Y * CHUNK_Z),
	};

	for (int x = 0; x < CHUNK_X; x++)
		for (int z = 0; z < CHUNK_Z; z++)
		{
			int height = fnlGetNoise2D(&noiseConfig, x, z) * 10;

			ret.blocks[getBlockIndex(x, height, z)] = (Block){
				.blockType = BLOCK_TYPE_GRASS,
			};

			for (int y = 0; y < height; y++)
			{
				if (height - y < 2)
					ret.blocks[getBlockIndex(x, y, z)].blockType = BLOCK_TYPE_GRASS;
				else
					ret.blocks[getBlockIndex(x, y, z)].blockType = BLOCK_TYPE_STONE;
			}
		}

	return ret;
}
