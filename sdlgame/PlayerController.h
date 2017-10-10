// PlayerController will get status of InputManager
// (keyboard buttons pressed, joystick axes and
// buttons pressed etc).
#pragma once
class PlayerController
{
public:
	PlayerController();
	PlayerController(Character *_owner);
	void Init(Character *_owner);

	void press_button(int button);
	void release_button(int button);
	void update_axis(int axis, float value);

	void round_axes();

	void tick(unsigned int delta_time);

	~PlayerController();
private:
	Character *owner;
	float axes[2];
	bool buttons[12];

};