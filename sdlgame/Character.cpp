#include <vector>
#include <math.h>

#include "Character.h"

Character::Character()
{
	Init(0, 0);
}

Character::Character(int xp, int yp)
{
	Init(xp, yp);
}

void Character::Init(int xp, int yp)
{
	speed = 2;
	x_pos = xp;
	y_pos = yp;
}

int Character::move(int new_x, int new_y)
{
	x_pos = new_x;
	y_pos = new_y;
	return 0;
}

int Character::push(float x_dir, float y_dir)
{
	printf("%f , %f\n", x_dir, y_dir);
	x_pos += (x_dir * (float)speed);
	y_pos += (y_dir * (float)speed);
	return 0;
}

void Character::tick()
{
}


Character::~Character()
{
}
