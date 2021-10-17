#include <ct/glt.h>
#include <stb_image.h>

#include <string.h>

#include "assert.h"
#include "renderer.h"
#include "texture.h"

char* textureFilenames[NUM_TEXTURES] = {
	"textures/cobblestone.png",
	"textures/dirt.png",
	"textures/grass_side.png",
	"textures/grass_top.png",
};

struct TextureConfig textureConfig[NUM_BLOCKS] = {
	{BLOCK_TYPE_AIR, {-1, -1, -1, -1, -1, -1}},
	{BLOCK_TYPE_STONE, {0, 0, 0, 0, 0, 0}},
	{BLOCK_TYPE_GRASS, {2, 2, 1, 3, 2, 2}},
	{BLOCK_TYPE_DIRT, {1, 1, 1, 1, 1, 1}},
};

float findTextureId(Block block, int face)
{
	struct TextureConfig config = textureConfig[block.blockType];

	return (float) config.texturePaths[face] / (NUM_TEXTURES - 1);
}

GLuint generate3DTexture()
{
	GLuint ret;
	glGenTextures(1, &ret);
	glBindTexture(GL_TEXTURE_3D, ret);

	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	typedef unsigned char u8;
	u8* texture_data = malloc(sizeof(u8) * NUM_TEXTURES * 16 * 16 * 3);

	for (int i = 0; i < NUM_TEXTURES; i++)
	{
		int width, height, num_channels;
		u8* stbi_image = stbi_load(
			textureFilenames[i], &width, &height, &num_channels, STBI_rgb);

		memcpy(&texture_data[16 * 16 * 3 * i], stbi_image, sizeof(u8) * 16 * 16 * 3);
		stbi_image_free(stbi_image);
	}

	glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB8, 16, 16, NUM_TEXTURES, 0, GL_RGB, GL_UNSIGNED_BYTE,
		texture_data);

	free(texture_data);
	return ret;
}
