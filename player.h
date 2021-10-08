#pragma once

#include <ct/glt.h>
#include <cglm/struct.h>

typedef struct
{
	vec3s pos;
	vec2s angle;
} Player;

void updatePlayer(Player* player, GLFWwindow* window);
mat4s createViewMat(Player player);
