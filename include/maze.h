#ifndef _MAZE_H_
#define _MAZE_H_

#define PI 3.14159265

#define ROWS 13
#define COLS 20
#define TILE_SIZE 64

#define WINDOW_WIDTH (COLS * TILE_SIZE)
#define WINDOW_HEIGHT (ROWS * TILE_SIZE)

#define MAP_SCALE 1.0

#define FPS 30
#define FRAME_TIME (1000 / FPS)

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

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

/**
 * struct Player - defines all the variables that a player (camera) has
 *
 * @x: x-coordinates of the player
 * @y: y-coordinates of the player
 * @w: width of the player
 * @h: height of the player
 * @turnDirection: -1 for left ; 1 for right
 * @walkDirection: -1 for backward ; 1 for forward
 * @rotAngle:  rotation angle of the player
 * @walkSpeed:     walk speed of the player
 * @rotSpeed:  rotation speed of the player
*/
typedef struct Player
{
	float x;
	float y;
	float w;
	float h;
	int turnDirection;
	int walkDirection;
	float rotAngle;
	float walkSpeed;
	float rotSpeed;
} Player;

int init_instance(SDL_Instance *instance);
void destroy(SDL_Instance *instance);

void setup(Player *player);
void process(Player *player, int *game_state);
void update(Player *player, int *last_frame_time);
void movePlayer(Player *player, float Dt);

void render(SDL_Instance *instance, Player *player, const int (*map)[COLS]);
void renderPlayer(SDL_Instance *instance, Player *player);
void renderMap(SDL_Instance *instance, const int (*map)[COLS]);
float scaler(float value);


#endif /* _MAZE_H_ */
