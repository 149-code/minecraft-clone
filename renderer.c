#include <cglm/struct.h>
#include <ct/glt.h>

#include "cubeMesh.h"
#include "renderer.h"

GLTvertexStore configChunkVertexStore()
{
	GLTvertexStore ret = gltCreateVertexStore(2);

	gltUseVertexStoreBuffer(ret, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(0);

	gltUseVertexStoreBuffer(ret, 1);
	glVertexAttribPointer(1, 4, GL_FLOAT, false, sizeof(mat4s), (void*) 0);
	glVertexAttribPointer(2, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (1 * sizeof(vec4s)));
	glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (2 * sizeof(vec4s)));
	glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (3 * sizeof(vec4s)));

	glEnableVertexAttribArray(1);
	glVertexAttribDivisor(1, 1);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);
	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);

	return ret;
}

void drawChunk(Chunk chunk, mat4s vp, GLuint shader, GLTvertexStore vs)
{
	int blockColorUniform = glGetUniformLocation(shader, "blockColor");
 	int vpUniform = glGetUniformLocation(shader, "vp");
	glUniformMatrix4fv(vpUniform, 1, false, &vp.m00);

	glUniform3f(blockColorUniform, 1.0, 1.0, 1.0);
	glUseProgram(shader);

	for (int i = 0; i < 6; i++)
	{
		gltVertexStoreSetData(
			vs, 0, sizeof(vec3s) * 6, cubeMesh[6 * i], GL_DYNAMIC_DRAW);
		gltVertexStoreSetData(vs, 1, chunk.faceTransformsLen[i] * sizeof(mat4s),
			chunk.faceTransforms[i], GL_DYNAMIC_DRAW);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, chunk.faceTransformsLen[i]);
	}
}
