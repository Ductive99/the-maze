#include "demo.h"

int init_instance(SDL_Instance *instance)
{
	/* Initialize SDL*/
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		fprintf(stderr, "Unable to intiliaze SDL: %s\n", SDL_GetError());
		return (1);
	}

	/* Create a new Window instancec */
	instance->window = SDL_CreateWindow("SDL2 \\o/", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1260, 730, 0);
	if (instance->window == NULL)
	{
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

	/*Create a new Renderer instance linked to the Window */
	instance->renderer = SDL_CreateRenderer(instance->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (instance->renderer == NULL)
	{
		SDL_DestroyWindow(instance->window);
		fprintf(stderr, "SDL_CreateRendere Error: %s\n", SDL_GetError());
		SDL_Quit();
		return (1);
	}

}

void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2)
{
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
