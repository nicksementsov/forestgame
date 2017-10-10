#include "movement_component.h"



movement_component::movement_component()
{
	Init(0.0f, 0.0f, 0.0f);
}

void movement_component::Init(float __x, float __y, float __rot)
{
	_x = __x;
	_y = __y;
	_rot = __rot;
}

float movement_component::x()
{
	return _x;
}

float movement_component::y()
{
	return _y;
}

float movement_component::rot()
{
	return _rot;
}

void movement_component::set_x(float __x)
{
	_x = __x;
}

void movement_component::set_y(float __y)
{
	_y = __y;
}

void movement_component::set_rot(float __rot)
{
	_rot = __rot;
}


movement_component::~movement_component()
{
}
