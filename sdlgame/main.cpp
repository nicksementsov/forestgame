#include <stdio.h>
#include <vector>
#include <math.h>
#include "SDLGame.h"
#include "Character.h"

bool debug = true;

#define SCREEN_W 1280
#define SCREEN_H 720

std::vector<int> testar;

int set_fps = 30;
SDL_Window* main_window;
SDL_Renderer* main_renderer;

unsigned int current_time = 0;

Character character_list[32];
Character* player = &character_list[0];
int character_count = 0;

// 0 - W, 1 = S, 2 = A, 3 = D
int wasd_states[4];


bool has_input()
{
	for (int i = 0; i < 4; i++)
	{
		if ((wasd_states[i]) || (wasd_states[i] == -1))
		{ 
			return true; 
		}
	}
	return false;
}

// Manage keyboard events and store keyboard state
bool handle_input(SDL_Event new_input)
{
	switch (new_input.type)
	{
	default:
		break;
	case SDL_KEYUP:
		switch (new_input.key.keysym.scancode)
		{
		default:
			break;
		case SDL_SCANCODE_W:
			wasd_states[0] = 0;
			break;
		case SDL_SCANCODE_S:
			wasd_states[1] = 0;
			break;
		case SDL_SCANCODE_A:
			wasd_states[2] = 0;
			break;
		case SDL_SCANCODE_D:
			wasd_states[3] = 0;
			break;
		}
		break;
	case SDL_KEYDOWN:
		switch (new_input.key.keysym.scancode)
		{
		default:
			break;
		case SDL_SCANCODE_W:
			wasd_states[0] = 1;
			break;
		case SDL_SCANCODE_S:
			wasd_states[1] = 1;
			break;
		case SDL_SCANCODE_A:
			wasd_states[2] = 1;
			break;
		case SDL_SCANCODE_D:
			wasd_states[3] = 1;
		case SDL_SCANCODE_1:
			set_fps = 60;
			break;
		case SDL_SCANCODE_2:
			set_fps = 30;
			break;
		case SDL_SCANCODE_3:
			set_fps = 15;
			break;
		case SDL_SCANCODE_ESCAPE:
			return false;
		}
		break;
	
	}

	return true;
}

float *key_to_stick()
{
	float *stick = new float[2];
	stick[0] = 0.0f;
	stick[1] = 0.0f;

	if ((!wasd_states[0] && !wasd_states[1]) || (wasd_states[0] && wasd_states[1]))
	{
		stick[1] = 0.0f;
	}
	else if (wasd_states[0])
	{
		stick[1] = -1.0f;
	}
	else
	{
		stick[1] = 1.0f;
	}

	if ((!wasd_states[2] && !wasd_states[3]) || (wasd_states[2] && wasd_states[3]))
	{
		stick[0] = 0.0f;
	}
	else if (wasd_states[2])
	{
		stick[0] = -1.0f;
	}
	else
	{
		stick[0] = 1.0f;
	}

	if (abs(stick[0]) && abs(stick[1]))
	{
		stick[0] *= 0.7f;
		stick[1] *= 0.7f;
	}

	return stick;
}

int debug_render_frame()
{
	SDL_SetRenderDrawColor(main_renderer, 0, 255, 0, 255);
	SDL_Rect new_rect;
	new_rect.h = 15;
	new_rect.w = 15;
	for (int i = 0; i < character_count; i++)
	{
		new_rect.x = character_list[i].x_pos - 7;
		new_rect.y = character_list[i].y_pos - 7;
		SDL_RenderDrawRect(main_renderer, &new_rect);
	}
	return 0;
}

int render_frame()
{
	SDL_SetRenderDrawColor(main_renderer, 120, 0, 255, 255);
	SDL_RenderClear(main_renderer);

	if (debug) debug_render_frame();

	SDL_RenderPresent(main_renderer);

	return 0;
}

int main_loop()
{
	bool running = true;
	SDL_Event new_event;

	unsigned int last_frame_time = SDL_GetTicks();
	unsigned int last_tick_time = SDL_GetTicks();
	while (running)
	{
		current_time = SDL_GetTicks();
		int has_events = SDL_PollEvent(&new_event);
		if (running && has_events)
		{
			switch (new_event.type)
			{
			default:
				break;
			case SDL_QUIT:
				running = false;
				SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
				SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Quitting application\n");
				break;
			case SDL_KEYUP:
				running = handle_input(new_event);
				break;
			case SDL_KEYDOWN:
				running = handle_input(new_event);
				break;
			}
		}
		if (current_time > (last_tick_time + (1000 / 120)))
		{
			last_tick_time = current_time;
			if (has_input())
			{
				float *axes = key_to_stick();
				player->push(axes[0], axes[1]);
			}
			for (int i = 0; i < character_count; i++)
			{
				character_list[i].tick();
			}
		}
		if (current_time > (last_frame_time + (1000 / set_fps)))
		{
			last_frame_time = current_time;
			render_frame();
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	//Init and Debug
	SDL_LogSetAllPriority(SDL_LOG_PRIORITY_DEBUG);
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Entering Application\n");
	SDL_Init(SDL_INIT_VIDEO);

	//Setup
	main_window = SDL_CreateWindow("sdlgame", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_RESIZABLE);
	main_renderer = SDL_CreateRenderer(main_window, -1, SDL_RENDERER_ACCELERATED);

	character_list[0] = Character(300, 360);
	character_count += 1;

	//Start
	int loop_exit_status = main_loop();

	//Quit
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;
}