#include <cglm/struct.h>
#include <ct/glt.h>

#include "cubeMesh.h"
#include "renderer.h"

GLTvertexStore configChunkVertexStore()
{
	GLTvertexStore ret = gltCreateVertexStore(3);

	gltUseVertexStoreBuffer(ret, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 5, NULL);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1, 2, GL_FLOAT, false, sizeof(float) * 5, (void*) (sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	gltUseVertexStoreBuffer(ret, 1);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, 0, NULL);
	glEnableVertexAttribArray(2);
	glVertexAttribDivisor(2, 1);

	gltUseVertexStoreBuffer(ret, 2);
	glVertexAttribPointer(3, 4, GL_FLOAT, false, sizeof(mat4s), (void*) 0);
	glVertexAttribPointer(4, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (1 * sizeof(vec4s)));
	glVertexAttribPointer(5, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (2 * sizeof(vec4s)));
	glVertexAttribPointer(6, 4, GL_FLOAT, false, sizeof(mat4s), (void*) (3 * sizeof(vec4s)));

	glEnableVertexAttribArray(3);
	glVertexAttribDivisor(3, 1);
	glEnableVertexAttribArray(4);
	glVertexAttribDivisor(4, 1);
	glEnableVertexAttribArray(5);
	glVertexAttribDivisor(5, 1);
	glEnableVertexAttribArray(6);
	glVertexAttribDivisor(6, 1);

	return ret;
}

void drawChunk(Chunk chunk, mat4s vp, GLuint shader, GLuint texture, GLTvertexStore vs)
{
	int vpUniform = glGetUniformLocation(shader, "vp");
	glUniformMatrix4fv(vpUniform, 1, false, &vp.m00);

	glUseProgram(shader);

	for (int i = 0; i < 6; i++)
	{
		gltVertexStoreSetData(vs, 0, sizeof(float) * 30, cubeMesh[6 * i], GL_DYNAMIC_DRAW);
 		gltVertexStoreSetData(vs, 1, chunk.numInstances[i] * sizeof(float),
			chunk.faceTextureIds[i], GL_DYNAMIC_DRAW);
		gltVertexStoreSetData(vs, 2, chunk.numInstances[i] * sizeof(mat4s),
			chunk.faceTransforms[i], GL_DYNAMIC_DRAW);

		glDrawArraysInstanced(GL_TRIANGLES, 0, 6, chunk.numInstances[i]);
	}
}
