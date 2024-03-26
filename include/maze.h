#ifndef _MAZE_H_
#define _MAZE_H_


#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define FPS 30
#define FRAME_TARGET_TIME (1000 / FPS)

#include <SDL2/SDL.h>
#include <stdbool.h>
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

typedef struct game_object {
    float x;
    float y;
    float width;
    float height;
    float vel_x;
    float vel_y;
} game_object;

int init_instance(SDL_Instance *instance);
void setup(game_object *ball);
void process(int *game_state);
void update(game_object *ball, int *last_frame_time);
void render(SDL_Instance *instance, game_object *ball);
void destroy(SDL_Instance *instance);

#endif /* _MAZE_H_ */
