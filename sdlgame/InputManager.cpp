#include "InputManager.h"

#include <math.h>
#include <SDL.h>

#include "SDLGame.h"
#include "PlayerController.h"

InputManager::InputManager()
{

}

InputManager::InputManager(PlayerController *_pcontroller)
{
	Init(_pcontroller);
}

void InputManager::Init(PlayerController *_pcontroller)
{
	pcontroller = _pcontroller;
	fill_array(button_states, 12, false);
	fill_array(axis_values, 2, 0.0f);

	axis_keybinds[0] = SDL_SCANCODE_A;
	axis_keybinds[1] = SDL_SCANCODE_D;

	axis_keybinds[2] = SDL_SCANCODE_W;
	axis_keybinds[3] = SDL_SCANCODE_S;

	keybinds[0] = SDL_SCANCODE_SPACE;
	keybinds[11] = SDL_SCANCODE_ESCAPE;
}

//TODO:: Make this function better/more accurate
void InputManager::circularize_axes()
{
	if (abs(axis_values[0]) && abs(axis_values[1]))
	{
		axis_values[0] *= 0.7f;
		axis_values[1] *= 0.7f;
	}
}

void InputManager::axis_by_key(int _axis, float value, float else_value)
{
	if (axis_values[_axis] != (value * -1.0f))
	{
		axis_values[_axis] = value;
	}
	else
	{
		axis_values[_axis] = else_value;
	}
}

void InputManager::key_pressed_to_axis(int key_pressed)
{
	switch (key_pressed)
	{
	default:
		break;
	case 0:
		axis_by_key(0, -1.0f, 0.0f);
		break;
	case 1:
		axis_by_key(0, 1.0f, 0.0f);
		break;
	case 2:
		axis_by_key(1, -1.0f, 0.0f);
		break;
	case 3:
		axis_by_key(1, 1.0f, 0.0f);
	}
}

void InputManager::key_released_to_axis(int key_pressed)
{
	switch (key_pressed)
	{
	default:
		break;
	case 0:
		axis_by_key(0, 0.0f, 1.0f);
		break;
	case 1:
		axis_by_key(0, 0.0f, -1.0f);
		break;
	case 2:
		axis_by_key(1, 0.0f, 1.0f);
		break;
	case 3:
		axis_by_key(1, 0.0f, -1.0f);
	}
}

void InputManager::handle_keyboard_input(SDL_Event new_event)
{
	int key_pressed = get_keybind(new_event.key.keysym.scancode);
	if (key_pressed != -1)
	{
		if (new_event.key.state == SDL_PRESSED)
		{
			button_states[key_pressed] = true;
			pcontroller->press_button(key_pressed);
		}
		else if (new_event.key.state == SDL_RELEASED)
		{
			button_states[key_pressed] = false;
			pcontroller->release_button(key_pressed);
		}
	}
	else
	{
		key_pressed = get_axis_keybind(new_event.key.keysym.scancode);
		if (key_pressed != -1)
		{
			if (new_event.key.state == SDL_PRESSED)
			{
				key_pressed_to_axis(key_pressed);
			}
			else if (new_event.key.state == SDL_RELEASED)
			{
				key_released_to_axis(key_pressed);
			}
			circularize_axes();
			pcontroller->update_axis(0, axis_values[0]);
			pcontroller->update_axis(1, axis_values[1]);
		}
	}
	// If we got here then the key pressed isn't bound to antyhing
}

int InputManager::get_keybind(SDL_Scancode new_key)
{
	for (int i = 0; i < 12; i++)
	{
		if (keybinds[i] == new_key)
		{
			return i;
		}
	}
	return -1;
}

int InputManager::get_axis_keybind(SDL_Scancode new_key)
{
	for (int i = 0; i < 4; i++)
	{
		if (axis_keybinds[i] == new_key)
		{
			return i;
		}
	}
	return -1;
}

InputManager::~InputManager()
{
}