#pragma once
class Character
{
public:
	Character();
	Character(int xp, int yp);
	void Init(int xp, int yp);

	int move(int new_x, int new_y);

	void tick(unsigned int delta_time);

	int speed;

	MovementComponent *movement;
	~Character();
};

