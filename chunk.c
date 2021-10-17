#include <cglm/struct.h>

#include "chunk.h"
#include "renderer.h"
#include "texture.h"
#include "perlin.h"

bool isTransparent(int blockType)
{
	if (blockType == BLOCK_TYPE_AIR)
		return true;
	else
		return false;
}

void computeVisableFaces(Chunk* chunk)
{
	for (int x = 0; x < CHUNK_X; x++)
		for (int y = 0; y < CHUNK_Y; y++)
			for (int z = 0; z < CHUNK_Z; z++)
			{
				int index = getBlockIndex(x, y, z);

				if (chunk->blocks[index].blockType == BLOCK_TYPE_AIR)
					continue;

				u8 visibleFaces = 0;

				if (x == 0 ||
					isTransparent(chunk->blocks[getBlockIndex(x - 1, y, z)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << X_MINUS);
				}
				if (x == CHUNK_X - 1 ||
					isTransparent(chunk->blocks[getBlockIndex(x + 1, y, z)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << X_PLUS);
				}
				if (y == 0 ||
					isTransparent(chunk->blocks[getBlockIndex(x, y - 1, z)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << Y_MINUS);
				}
				if (y == CHUNK_Y - 1 ||
					isTransparent(chunk->blocks[getBlockIndex(x, y + 1, z)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << Y_PLUS);
				}
				if (z == 0 ||
					isTransparent(chunk->blocks[getBlockIndex(x, y, z - 1)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << Z_MINUS);
				}
				if (z == CHUNK_Z - 1 ||
					isTransparent(chunk->blocks[getBlockIndex(x, y, z + 1)]
							      .blockType))
				{
					visibleFaces = visibleFaces | (1 << Z_PLUS);
				}

				chunk->blocks[index].faceBitMask = visibleFaces;
			}
}

void computeFaceTransforms(Chunk* chunk)
{
	int blockIndex = 0;
	for (int i = 0; i < 6; i++)
		chunk->numInstances[i] = 0;

	for (int x = 0; x < CHUNK_X; x++)
		for (int y = 0; y < CHUNK_Y; y++)
			for (int z = 0; z < CHUNK_Z; z++)
			{
				for (int i = 0; i < 6; i++)
				{

					if (chunk->blocks[blockIndex].faceBitMask & (1 << i))
					{
						chunk->faceTransforms[i]
								     [chunk->numInstances[i]] =
							glms_translate(glms_mat4_identity(),
								glms_vec3_add((vec3s){x, y, z},
									chunk->pos));

						chunk->faceTextureIds[i]
								     [chunk->numInstances[i]] =
							findTextureId(chunk->blocks[blockIndex], i);

						chunk->numInstances[i] += 1;
					}
				}

				blockIndex += 1;
			}
}

Chunk generateRandomChunk(vec3s pos)
{
	Chunk ret = initChunk(pos);

	for (int x = 0; x < CHUNK_X; x++)
		for (int z = 0; z < CHUNK_Z; z++)
		{
			int height = Perlin_Get2d(pos.x + x, pos.z + z, 0.1, 2) * 20;

			ret.blocks[getBlockIndex(x, height, z)] = (Block){
				.blockType = BLOCK_TYPE_GRASS,
			};

			for (int y = 0; y < height; y++)
			{
				if (height == y - 1)
					ret.blocks[getBlockIndex(x, y, z)].blockType =
						BLOCK_TYPE_GRASS;
				else if (height - y < 2)
					ret.blocks[getBlockIndex(x, y, z)].blockType =
						BLOCK_TYPE_DIRT;
				else
					ret.blocks[getBlockIndex(x, y, z)].blockType =
						BLOCK_TYPE_STONE;
			}
		}

	return ret;
}

Chunk initChunk(vec3s pos)
{
	Chunk ret = {
		.pos = pos,
		.blocks = malloc(sizeof(Block) * CHUNK_X * CHUNK_Y * CHUNK_Z),
	};

	for (int i = 0; i < 6; i++)
	{
		ret.faceTransforms[i] = aligned_alloc(64, sizeof(mat4s) * 2048);
		ret.faceTextureIds[i] = malloc(sizeof(float) * 2048);
	}

	return ret;
}
