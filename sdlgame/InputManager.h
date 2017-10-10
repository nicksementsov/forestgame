#pragma once
class InputManager
{
public:
	InputManager(PlayerController *_pcontroller);
	void Init(PlayerController *_pcontroller);

	void circularize_axes();
	void axis_by_key(int _axis, float value, float else_value);
	void key_pressed_to_axis(int key_pressed);
	void key_released_to_axis(int key_pressed);
	void handle_keyboard_input(SDL_Event new_event);
	int get_keybind(SDL_Scancode new_key);
	int get_axis_keybind(SDL_Scancode new_key);


	~InputManager();

private:
	PlayerController *pcontroller;

	bool button_states[12];
	float axis_values[2];

	SDL_Scancode axis_keybinds[4];
	SDL_Scancode keybinds[12];
};

