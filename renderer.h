#pragma once

#include <ct/glt.h>
#include <cglm/struct.h>

#include "chunk.h"
#include "blockType.h"

enum BlockFaces
{
	X_MINUS,
	X_PLUS,
	Y_MINUS,
	Y_PLUS,
	Z_MINUS,
	Z_PLUS
};

struct GltVertexStore configChunkVertexStore();
void drawChunk(Chunk chunk, mat4s vp, GLuint shader, GLuint texture, struct GltVertexStore vs);
