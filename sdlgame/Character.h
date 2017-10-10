#pragma once
class Character
{
public:
	Character();
	Character(int xp, int yp);
	void Init(int xp, int yp);
	int move(int new_x, int new_y);
	int push(float x_dir, float y_dir);
	void tick();

	int x_pos;
	int y_pos;
	int speed;

	~Character();
};

