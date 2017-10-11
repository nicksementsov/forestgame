#include "Character.h"

#include <vector>
#include <math.h>

#include "MovementComponent.h"

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

	movement = new MovementComponent(xp, yp);
}

int Character::move(int new_x, int new_y)
{
	return 0;
}

void Character::tick(unsigned int delta_time)
{

}


Character::~Character()
{
}
