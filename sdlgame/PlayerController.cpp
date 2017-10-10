#include "SDLGame.h"

PlayerController::PlayerController()
{
	Init(new Character());
}

PlayerController::PlayerController(Character *_owner)
{
	Init(_owner);
}

void PlayerController::Init(Character *_owner)
{
	owner = _owner;
	fill_array(axes, 2, 0.0f);
	fill_array(buttons, 12, false);
}

void PlayerController::press_button(int button)
{
	buttons[button] = true;
}

void PlayerController::release_button(int button)
{
	buttons[button] = false;
}

void PlayerController::update_axis(int axis, float value)
{
	axes[axis] = value;
}

void PlayerController::round_axes()
{
	axes[0] *= 0.7f;
	axes[1] *= 0.7f;
}

void PlayerController::tick(unsigned int delta_time)
{
}


PlayerController::~PlayerController()
{
}