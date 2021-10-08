#include "cubeMesh.h"

float cubeZMinus[6][3] = {
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
};

float cubeZPlus[6][3] = {
	{0.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
};

float cubeXMinus[6][3] = {
	{0.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 0.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 1.0f, 1.0f},
};

float cubeXPlus[6][3] = {
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
};

float cubeYMinus[6][3] = {
	{0.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 0.0f},
	{1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 0.0f},
};

float cubeYPlus[6][3] = {
	{0.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 0.0f},
	{1.0f, 1.0f, 1.0f},
	{1.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 0.0f},
};
