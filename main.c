#define GLT_IMPL
#define STB_IMAGE_IMPLEMENTATION
#include <ct/glt.h>
#include <stb_image.h>

#include <cglm/struct.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "renderer.h"
#include "chunk.h"
#include "player.h"
#include "texture.h"

void printMat4(mat4s mat)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			printf("%f ", mat.raw[col][row]);
		}

		puts("");
	}
}

int main()
{
	GLFWwindow* window = gltCreateDefaultContext(500, 500, "", NULL);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	GLuint shader = gltCreateShader("cube/shader.vert", "cube/shader.frag");
	GLTvertexStore chunkVs = configChunkVertexStore();
	Player player = {{-5, 10, -5}, {glm_rad(-45), glm_rad(-30)}};
	GLuint texture = generate3DTexture();

	Chunk chunks[100];

	for (int x = 0; x < 10; x++)
		for (int y = 0; y < 10; y++)
		{
			chunks[x * 10 + y] = generateRandomChunk((vec3s) {16 * x, 0, 16 * y});
			computeVisableFaces(&chunks[x * 10 + y]);
			computeFaceTransforms(&chunks[x * 10 + y]);
		}

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CW); 

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		updatePlayer(&player, window);

		int width, height;
		glfwGetWindowSize(window, &width, &height);
		mat4s projection = glms_perspective(glm_rad(45), (float) width / height, 0.1, 100);
		mat4s view = createViewMat(player);
		mat4s vp = glms_mat4_mul(projection, view);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (int i = 0; i < 100; i++)
			drawChunk(chunks[i], vp, shader, texture, chunkVs);

		glfwSwapBuffers(window);
	}
}
