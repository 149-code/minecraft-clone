#pragma once

#include <cglm/struct.h>
#include <FastNoiseLite.h>

#define CHUNK_X 16
#define CHUNK_Y 256
#define CHUNK_Z 16

typedef unsigned char u8;

typedef struct
{
	u8 blockType;
	u8 faceBitMask;
} Block;

typedef struct
{
	vec3s pos;
	Block* blocks;
} Chunk;

void computeVisableFaces(Chunk* c);
bool isTransparent(int blockType);
Chunk generateRandomChunk(vec3s pos, fnl_state noiseConfig);

static inline int getBlockIndex(int x, int y, int z)
{
	return x * CHUNK_Y * CHUNK_Z + y * CHUNK_Z + z;
}

