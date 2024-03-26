#include "maze.h"

/**
 * setup - initializes an object to move at a certain speed.
 *
 * @ball: pointer to the game object.
*/
void setup(game_object *ball)
{
	ball->x = 10;
	ball->y = 20;
	ball->width = 20;
	ball->height = 20;
	ball->vel_x = 180;
	ball->vel_y = 140;
}

/**
 * process - process user's input to quit.
 *
 * @game_state: variable to end the loop.
*/
void process(int *game_state)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				*game_state = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					*game_state = false;
				break;
		}
	}
}

/**
 * update - handles updating the frames and wall collisions.
 *
 * @ball: pointer to the game object.
 * @last_frame_time: time since the last frame.
*/
void update(game_object *ball, int *last_frame_time)
{
	float delta_time = (SDL_GetTicks() - *last_frame_time) / 1000.0;

	*last_frame_time = SDL_GetTicks();

	ball->x += ball->vel_x * delta_time;
	ball->y += ball->vel_y * delta_time;

	if (ball->x < 0)
	{
		ball->x = 0;
		ball->vel_x = -ball->vel_x;
	}
	if (ball->x + ball->height > WINDOW_WIDTH)
	{
		ball->x = WINDOW_WIDTH - ball->width;
		ball->vel_x = -ball->vel_x;
	}
	if (ball->y < 0)
	{
		ball->y = 0;
		ball->vel_y = -ball->vel_y;
	}
	if (ball->y + ball->height > WINDOW_HEIGHT)
	{
		ball->y = WINDOW_HEIGHT - ball->height;
		ball->vel_y = -ball->vel_y;
	}
}

/**
 * render - renders the frame.
 *
 * @instance: pointer to the window and renderer.
 * @ball: pointer to the game object.
*/
void render(SDL_Instance *instance, game_object *ball)
{
	SDL_SetRenderDrawColor(instance->renderer, 0, 0, 0, 255);
	SDL_RenderClear(instance->renderer);

	SDL_Rect ball_rect = {
		(int)ball->x,
		(int)ball->y,
		(int)ball->width,
		(int)ball->height
	};
	SDL_SetRenderDrawColor(instance->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(instance->renderer, &ball_rect);

	SDL_RenderPresent(instance->renderer);
}

/**
 * destroy - destroys renderer and window instances.
 *
 * @instance: pointer to the window and renderer.
*/
void destroy(SDL_Instance *instance)
{
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	SDL_Quit();
}
