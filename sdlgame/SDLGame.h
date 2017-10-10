#pragma once
#include "SDLGame.h"
#include "MovementComponent.h"
#include "Character.h"
#include "PlayerController.h"
#include "InputManager.h"
#include <algorithm>

typedef struct
{
	float x;
	float y;

	bool operator==(Vector2D other)
	{
		return ((x == other.x) && (y == other.y));
	}
} Vector2D;

static void fill_array(int* _array, int length, int value)
{
	std::fill(_array, _array +length, value);
}

static void fill_array(char* _array, int length, char value)
{
	std::fill(_array, _array + length, value);
}

static void fill_array(float* _array, int length, float value)
{
	std::fill(_array, _array + length, value);
}

static void fill_array(bool* _array, int length, bool value)
{
	std::fill(_array, _array + length, value);
}