#include <stdio.h>
#include <vector>
#include <math.h>
#include <SDL.h>

#include "SDLGame.h"

#include "MovementComponent.h"
#include "Character.h"
#include "PlayerController.h"
#include "InputManager.h"

bool debug = true;

#define SCREEN_W 1280
#define SCREEN_H 720

int set_fps = 30;
SDL_Window* main_window;
SDL_Renderer* main_renderer;

unsigned int current_time = 0;

Character character_list[32];
Character* player = &character_list[0];
int character_count = 0;

PlayerController pcontroller0;
InputManager input_manager;

int debug_render_frame()
{
	SDL_SetRenderDrawColor(main_renderer, 0, 255, 0, 255);
	SDL_Rect new_rect;
	new_rect.h = 15;
	new_rect.w = 15;
	for (int i = 0; i < character_count; i++)
	{
		new_rect.x = character_list[i].movement->x() - 7;
		new_rect.y = character_list[i].movement->y() - 7;
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
			case SDL_KEYDOWN:
				input_manager.handle_keyboard_input(new_event);
				break;
			case SDL_KEYUP:
				input_manager.handle_keyboard_input(new_event);
				break;
			}
		}
		if (current_time > (last_tick_time + (1000 / 120)))
		{
			last_tick_time = current_time;
			for (int i = 0; i < character_count; i++)
			{
				character_list[i].tick(current_time);
				printf("%f, %f :: %f\n", character_list[i].movement->x(),
					character_list[i].movement->y(),
					character_list[i].movement->rot());
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

	*player = Character(300, 360);
	pcontroller0 = PlayerController(player);
	character_count += 1;

	//Start
	int loop_exit_status = main_loop();

	//Quit
	SDL_DestroyWindow(main_window);
	SDL_Quit();
	return 0;
}