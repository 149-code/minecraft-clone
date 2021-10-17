#pragma once

#include "blockType.h"
#include "renderer.h"

#define NUM_TEXTURES 4

struct BlockTexture
{
	int textureIds[6];
};

struct TextureConfig
{
	int blockType;
	int texturePaths[6];
};

char* textureFilenames[NUM_TEXTURES];
struct TextureConfig textureConfig[NUM_BLOCKS];
float findTextureId(Block block, int face);
GLuint generate3DTexture();
