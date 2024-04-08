#include "maze.h"

/**
 * init_instance - Initializes an SDL window and renderer.
 *
 * @instance: pointer to the SDL window and renderer.
 *
 * Return: (true) if initialization is successful, (false) otherwise.
*/
int init_instance(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return (false);
	}

	/* Window Initialization */
	instance->window = SDL_CreateWindow(
		"C ft. SDL",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WINDOW_WIDTH, WINDOW_HEIGHT,
		0
	);
	if (!instance->window)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return (false);
	}

	/* Renderer Initialization */
	instance->renderer = SDL_CreateRenderer(instance->window, -1, 0);
	if (!instance->renderer)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return (false);
	}
	SDL_SetRenderDrawBlendMode(instance->renderer, SDL_BLENDMODE_BLEND);

	return (true);
}

/**
 * destroy - destroys renderer and window instances.
 *
 * @instance: pointer to the window and renderer.
*/
void destroy(SDL_Instance *instance, SDL_Visuals *visuals)
{
	free(visuals->wallTexture);
	free(visuals->colorBuffer);
	SDL_DestroyTexture(visuals->texture);
	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	SDL_Quit();
}
