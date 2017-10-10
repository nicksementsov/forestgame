#pragma once
class movement_component
{
public:
	movement_component();

	float x();
	float y();
	float rot();
	void set_x(float __X);
	void set_y(float __y);
	void set_rot(float __rot);

	void translate(float *new_pos);
	void rotate(float new_rot);
	void tick(float time);

	~movement_component();
private:
	void Init(float __x, float __y, float __rot);

	float _x, _y;
	float _rot;

	// Targets
	float t_x, t_y;
	float t_rot;
};

