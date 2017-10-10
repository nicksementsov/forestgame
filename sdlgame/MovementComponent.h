#pragma once
class MovementComponent
{
public:
	MovementComponent();
	MovementComponent(float __x, float __y);

	float x();
	float y();
	float rot();

	float target_x();
	float target_y();
	float target_rot();

	float xs();
	float ys();
	float rots();

	void x(float __x);
	void y(float __y);
	void rot(float __rot);

	void target_x(float __x);
	void target_y(float __y);
	void target_rot(float __rot);

	void xs(float __xs);
	void ys(float __ys);
	void rots(float __rots);

	// Set our targets which we will interpolate to during each
	// tick.
	void translate(float __x, float __y);
	void rotate(float __rot);

	// Translate to our targets 
	void tick(unsigned int delta_time);

	// TODO: write a print format thing
	~MovementComponent();
private:
	void Init(float __x, float __y, float __rot);

	float _x, _y;
	float _rot;

	// Translate and rotate speeds
	float _xs, _ys;
	float _rots;

	// Targets
	float _t_x, _t_y;
	float _t_rot;
};

