#ifndef _DEMO_H_
#define _DEMO_H_

#include <SDL2/SDL.h>

typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

int init_instance(SDL_Instance *);
void draw_line(SDL_Renderer *renderer, int x1, int y1, int x2, int y2);

#endif /* _DEMO_H_ */
