#pragma once

#include <ct/glt.h>
#include <cglm/struct.h>

#include "chunk.h"
#include "blockType.h"

typedef struct CubeMesh
{
	GLTvertexStore faces[6];
} CubeMesh;

enum BlockFaces
{
	X_MINUS,
	X_PLUS,
	Y_MINUS,
	Y_PLUS,
	Z_MINUS,
	Z_PLUS
};

CubeMesh initCubeMesh();
void drawChunk(Chunk chunk, mat4s vp, GLuint shader, CubeMesh cm);
