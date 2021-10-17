#include <cglm/struct.h>
#include <math.h>

#include "player.h"

#define PLAYER_MS 0.5
#define PLAYER_VERT_MS 0.3
#define CURSOR_SENSE 500

vec2s prevCursorPos = (vec2s) {0, 0};

void updatePlayer(Player* player, GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	player->angle.x += (x - prevCursorPos.x) / -CURSOR_SENSE;
	player->angle.y += (y - prevCursorPos.y) / -CURSOR_SENSE;

	if (player->angle.y > M_PI_2 * 0.99)
		player->angle.y = M_PI_2 * 0.99;
	else if (player->angle.y < M_PI_2 * -0.99)
		player->angle.y = M_PI_2 * -0.99;

	printf("%f %f\n", player->angle.x, player->angle.y);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		player->pos = glms_vec3_add(player->pos,
			(vec3s){sin(player->angle.x) * PLAYER_MS, 0, cos(player->angle.x) * PLAYER_MS});
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		player->pos = glms_vec3_add(player->pos,
			(vec3s){sin(player->angle.x) * -PLAYER_MS, 0, cos(player->angle.x) * -PLAYER_MS});
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		player->pos = glms_vec3_add(player->pos,
			(vec3s){cos(player->angle.x) * PLAYER_MS, 0, sin(player->angle.x) * -PLAYER_MS});
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		player->pos = glms_vec3_add(player->pos,
			(vec3s){cos(player->angle.x) * -PLAYER_MS, 0, sin(player->angle.x) * PLAYER_MS});

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		player->pos.y += PLAYER_VERT_MS;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		player->pos.y -= PLAYER_VERT_MS;

	prevCursorPos = (vec2s) {x, y};
}

mat4s createViewMat(Player player)
{
	vec3s angle = {sin(player.angle.x), sin(player.angle.y),
		cos(player.angle.x) * cos(player.angle.y)};

	return glms_look(player.pos, angle, (vec3s){0, 1, 0});
}
