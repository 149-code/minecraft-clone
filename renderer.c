#include <cglm/struct.h>
#include <ct/glt.h>

#include "cubeMesh.h"
#include "renderer.h"

CubeMesh initCubeMesh()
{
	CubeMesh ret;

	ret.faces[X_MINUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(
		ret.faces[X_MINUS], 0, sizeof(cubeXMinus), cubeXMinus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	ret.faces[X_PLUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(ret.faces[X_PLUS], 0, sizeof(cubeXPlus), cubeXPlus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	ret.faces[Y_MINUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(
		ret.faces[Y_MINUS], 0, sizeof(cubeYMinus), cubeYMinus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	ret.faces[Y_PLUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(ret.faces[Y_PLUS], 0, sizeof(cubeYPlus), cubeYPlus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	ret.faces[Z_MINUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(
		ret.faces[Z_MINUS], 0, sizeof(cubeZMinus), cubeZMinus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	ret.faces[Z_PLUS] = gltCreateVertexStore(1);
	gltVertexStoreSetData(ret.faces[Z_PLUS], 0, sizeof(cubeZPlus), cubeZPlus, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	return ret;
}

void drawChunk(Chunk chunk, mat4s vp, GLuint shader, CubeMesh cm)
{
	glUseProgram(shader);

	for (int x = 0; x < CHUNK_X; x++)
		for (int y = 0; y < CHUNK_Y; y++)
			for (int z = 0; z < CHUNK_Z; z++)
			{
				int index = getBlockIndex(x, y, z);
				vec3s pos = glms_vec3_add(chunk.pos, (vec3s){x, y, z});

				mat4s mvp = glms_mat4_mul(
					vp, glms_translate(glms_mat4_identity(), pos));

				glUniformMatrix4fv(
					glGetUniformLocation(shader, "mvp"), 1, false, &mvp.m00);

				switch (chunk.blocks[index].blockType)
				{
				case BLOCK_TYPE_STONE:
					glUniform3f(glGetUniformLocation(shader, "blockColor"), 0.5,
						0.5, 0.5);
					break;
				case BLOCK_TYPE_GRASS:
					glUniform3f(glGetUniformLocation(shader, "blockColor"), 0.2,
						1.0, 0.4);
					break;
				}

				for (int i = 0; i < 6; i++)
				{
					if (chunk.blocks[index].faceBitMask & (1 << i))
					{
						gltUseVertexStore(cm.faces[i]);
						glDrawArrays(GL_TRIANGLES, 0, 6);
					}
				}
			}
}
