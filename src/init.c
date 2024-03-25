#include "maze.h"

int init(SDL_Instance *instance)
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return (1);
	}

    instance->window = SDL_CreateWindow("The Maze", SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
    if (instance->window == NULL)
    {
        fprintf(stderr, "Unable to Create Window: %s\n", SDL_GetError());
        SDL_Quit();
        return (1);
    }

    return (0);
}

