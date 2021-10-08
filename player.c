#include "player.h"

#define PLAYER_MS 0.5
#define PLAYER_VERT_MS 0.3

void updatePlayer(Player* player, GLFWwindow* window)
{
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	player->angle.x = x / -500;
	player->angle.y = y / -500;

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
}

mat4s createViewMat(Player player)
{
	vec3s angle = {sin(player.angle.x), sin(player.angle.y),
		cos(player.angle.x) * cos(player.angle.y)};

	return glms_look(player.pos, angle, (vec3s){0, 1, 0});
}
