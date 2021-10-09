#define GLT_IMPL
#define FNL_IMPL
#include <FastNoiseLite.h>
#include <ct/glt.h>
#include <cglm/struct.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "renderer.h"
#include "chunk.h"
#include "player.h"

// a a a:

Chunk createChunk()
{
	Chunk ret = {
		.pos = (vec3s) {0, 0, 0},
		.blocks = malloc(sizeof(Block) * CHUNK_X * CHUNK_Y * CHUNK_Z),
	};

	ret.blocks[0].blockType = BLOCK_TYPE_STONE;
	return ret;
}

int main()
{
	GLFWwindow* window = gltCreateDefaultContext(500, 500, "", NULL);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint shader = gltCreateShader("cube/shader.vert", "cube/shader.frag");
	CubeMesh cm = initCubeMesh();
	Player player = {{-5, 10, -5}, {glm_rad(45), glm_rad(-30)}};

	fnl_state noiseConfig = fnlCreateState();
	noiseConfig.noise_type = FNL_NOISE_OPENSIMPLEX2;
	noiseConfig.frequency = 0.05;

	Chunk chunks[25];
	for (int x = 0; x < 5; x++)
		for (int z = 0; z < 5; z++)
		{
			chunks[x * 5 + z] = generateRandomChunk((vec3s) {x * 16, 0, z * 16}, noiseConfig);
			computeVisableFaces(&chunks[x * 5 + z]);
		}

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		updatePlayer(&player, window);

		mat4s projection = glms_perspective(glm_rad(45), 1, 0.1, 100);
		mat4s view = createViewMat(player);
		mat4s vp = glms_mat4_mul(projection, view);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 25; i++)
			drawChunk(chunks[i], vp, shader, cm);

		glfwSwapBuffers(window);
	}
}
