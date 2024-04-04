#ifndef _MAZE_H_
#define _MAZE_H_


/*
TODOs:
	- Fix problem with raycasting into wall corners.
*/


#define PI 3.14159265

#define ROWS 13
#define COLS 20
#define TILE_SIZE 64

#define WINDOW_WIDTH (COLS * TILE_SIZE)
#define WINDOW_HEIGHT (ROWS * TILE_SIZE)

#define MAP_SCALE 1.0

#define FOV (60 * PI / 180)
#define RAYS WINDOW_WIDTH

#define FPS 30
#define FRAME_TIME (1000 / FPS)

#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

extern const int map[ROWS][COLS];

/**
 * struct SDL_Instance - Represents the SDL window and renderer
 *
 * @window: Pointer to the SDL_Window instance
 * @renderer: Pointer to the SDL_Renderer instance
*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;

/**
 * struct Player - Represents the player (camera) in the game world
 *
 * @x: X-coordinate of the player
 * @y: Y-coordinate of the player
 * @w: Width of the player
 * @h: Height of the player
 * @turnDirection: Direction of player's turning (-1 -> left, 1 -> right)
 * @walkDirection: Direction of player's walking (-1 -> backward, 1 -> forward)
 * @rotAngle: Rotation angle of the player
 * @walkSpeed: Walk speed of the player
 * @rotSpeed: Rotation speed of the player
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

/**
 * struct Ray - defines all the variables that a ray has
 *
 * @rayAngle: Angle of the ray relative to the player's orientation
 * @wallHitX: X-coordinate of the first intersection of the ray with a wall
 * @wallHitY: Y-coordinate of the first intersection of the ray with a wall
 * @distance: Distance from player to the first wall hit
 * @wasHitVertical: Signals if a vertical wall was hit (1 -> true, 0 -> false)
 * @UorD: Signals if the ray is facing up or down (0 -> up, 1 -> down)
 * @RorL: Signals if the ray is facing right or left (1 -> right, 0 -> left)
 * @wallHitContent: Content of the wall hit by the ray (according to the map)
*/
typedef struct Ray
{
	float rayAngle;
	float wallHitX;
	float wallHitY;
	float distance;
	int wasHitVertical;
	int UorD;
	int RorL;
	int wallHitContent;
} Ray;

int init_instance(SDL_Instance *instance);
void destroy(SDL_Instance *instance);

void setup(Player *player);
void process(Player *player, int *game_state);
void update(Player *player, int *last_frame_time);
void movePlayer(Player *player, float Dt);

void render(SDL_Instance *instance, Player *player);
void renderPlayer(SDL_Instance *instance, Player *player);
void renderRays(SDL_Instance *instance, Player *player);
void renderMap(SDL_Instance *instance);
void castRays(Player *player);
void castRay(Player *player, float rayAngle, int Id);


/* Helper Functions*/
bool isBlocked(float x, float y);
float scaler(float value);
float normalize(float angle);
float distanceBtwn(float x1, float y1, float x2, float y2);

#endif /* _MAZE_H_ */
