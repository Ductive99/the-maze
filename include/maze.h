#ifndef _MAZE_H_
#define _MAZE_H_

#include <SDL2/SDL.h>
#include <stdio.h>

/**
 * struct SDL_Instance - window and renderer
 *
 * @window: the window
 * @renderer: the renderer
*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init(SDL_Instance *instance);

#endif /* _MAZE_H_ */
