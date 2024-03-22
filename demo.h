#ifndef _DEMO_H_
#define _DEMO_H_

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

int init_instance(SDL_Instance *);
void draw_line(SDL_Instance instance);

#endif /* _DEMO_H_ */
