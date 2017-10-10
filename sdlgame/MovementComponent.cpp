#include "MovementComponent.h"

MovementComponent::MovementComponent()
{
	Init(0.0f, 0.0f, 0.0f);
}

MovementComponent::MovementComponent(float __x, float __y)
{
	Init(__x, __y, 0.0f);
}

void MovementComponent::Init(float __x, float __y, float __rot)
{
	_x = __x;
	_y = __y;
	_rot = __rot;
}

float MovementComponent::x()
{
	return _x;
}

float MovementComponent::y()
{
	return _y;
}

float MovementComponent::rot()
{
	return _rot;
}

float MovementComponent::target_x()
{
	return _t_x;
}

float MovementComponent::target_y()
{
	return _t_y;
}

float MovementComponent::target_rot()
{
	return _t_rot;
}

float MovementComponent::xs()
{
	return _xs;
}

float MovementComponent::ys()
{
	return _ys;
}

float MovementComponent::rots()
{
	return _rots;
}

void MovementComponent::x(float __x)
{
	_x = __x;
}

void MovementComponent::y(float __y)
{
	_y = __y;
}

void MovementComponent::rot(float __rot)
{
	_rot = __rot;
}

void MovementComponent::target_x(float __x)
{
	_t_x = __x;
}

void MovementComponent::target_y(float __y)
{
	_t_y = __y;
}

void MovementComponent::target_rot(float __rot)
{
	_t_rot = __rot;
}

void MovementComponent::xs(float __xs)
{
	_xs = __xs;
}

void MovementComponent::ys(float __ys)
{
	_ys = __ys;
}

void MovementComponent::rots(float __rots)
{
	_rots = __rots;
}

void MovementComponent::translate(float __x, float __y)
{
	_t_x = __x;
	_t_y = __y;
}

void MovementComponent::rotate(float __rot)
{
	_t_rot = __rot;
}

void MovementComponent::tick(unsigned int delta_time)
{
	if (_x != _t_x)
	{
		x(_x + (_xs * delta_time));
	}
	if (_y != _t_y)
	{
		y(_y + (_ys * delta_time));
	}
}


MovementComponent::~MovementComponent()
{
}
